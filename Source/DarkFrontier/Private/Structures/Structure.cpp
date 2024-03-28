// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

AStructure::AStructure()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	SpringArm->SetupAttachment(StaticMesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	AbilitySystemComponent = CreateDefaultSubobject<UStructureAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UStructureAttributeSet>("Attributes");
}

void AStructure::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	ApplyEffect(DefaultAttributes);
	for(const TSubclassOf<UGameplayEffect> PassiveEffectClass : PassiveEffectClasses)
	{
		ApplyEffect(PassiveEffectClass);
	}
}

void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(RootPart == nullptr) return;
	
	const float LinearMaxSpeed = Attributes->GetLinearMaxSpeed();
	const float LinearAccel = Attributes->GetLinearAcceleration();
	StaticMesh->AddImpulse(CalculateImpulse(StaticMesh->GetPhysicsLinearVelocity(), MoveInput, LinearMaxSpeed, LinearAccel, DeltaTime), NAME_None, true);

	const float AngularMaxSpeed = Attributes->GetAngularMaxSpeed();
	const float AngularAccel = Attributes->GetAngularAcceleration();
	StaticMesh->AddAngularImpulseInDegrees(CalculateImpulse(StaticMesh->GetPhysicsAngularVelocityInDegrees(), RotateInput, AngularMaxSpeed, AngularAccel, DeltaTime), NAME_None, true);
}

void AStructure::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	SetOwner(NewController); // For ASC mixed replication mode
}

bool AStructure::TryInit(AStructurePart* NewRoot)
{
	if(RootPart != nullptr) return false;
	if(NewRoot->GetOwningStructure() != nullptr) return false;
	
	NewRoot->TryInit(this);
	RootPart = NewRoot;
	RootPart->SetActorRelativeLocation(FVector::ZeroVector);
	RootPart->SetActorRelativeRotation(FRotator::ZeroRotator);

	return true;
}

AStructurePart* AStructure::GetRootPart() const
{
	return RootPart;
}

TArray<AStructurePart*> AStructure::GetParts()
{
	return Parts;
}

void AStructure::RegisterPart(AStructurePart* InPart, const bool SuppressEvent)
{
	InPart->TryInitPartId(NextPartId);
	NextPartId++;
	
	Parts.Add(InPart);
	InPart->OnRegistered();
	
	if(!SuppressEvent)
	{
		OnLayoutChanged.Broadcast();
	}
}

void AStructure::UnregisterPart(AStructurePart* InPart, const bool SuppressEvent)
{
	Parts.Remove(InPart);
	InPart->OnUnRegistered();

	if(!SuppressEvent)
	{
		OnLayoutChanged.Broadcast();
	}
}

bool AStructure::IsLayoutValid()
{
	return !IsLayoutSelfIntersecting() && !IsLayoutUpkeepOverloaded();
}

bool AStructure::IsLayoutSelfIntersecting()
{
	for(int i = 0; i < Parts.Num(); i++)
	{
		for(int j = i + 1; j < Parts.Num(); j++)
		{
			if(Parts[i]->IsOverlappingActor(Parts[j]))
			{
				return true;
			}
		}
	}
	return false;
}

bool AStructure::IsLayoutUpkeepOverloaded() const
{
	return GetUpkeep() > Attributes->GetMaxUpkeep();
}

void AStructure::UpdateLayoutInformation()
{
	// Collect reachable parts
	TArray<AStructurePart*> NewParts;
	NewParts.Add(RootPart);

	int CurrentIndex = 0;
	while(CurrentIndex < NewParts.Num())
	{
		for(const UStructurePartSlot* Slot : NewParts[CurrentIndex]->GetSlots())
		{
			if(Slot->GetAttachedSlot() != nullptr && !NewParts.Contains(Slot->GetAttachedSlot()->GetOwningPart()))
			{
				NewParts.Add(Slot->GetAttachedSlot()->GetOwningPart());
			}
		}
		CurrentIndex++;
	}

	// Call register and unregister events as needed
	for(AStructurePart* Part : NewParts)
	{
		if(!Parts.Contains(Part))
		{
			RegisterPart(Part, true);
		}
	}

	CurrentIndex = 0;
	while(CurrentIndex < Parts.Num())
	{
		if(!NewParts.Contains(Parts[CurrentIndex]))
		{
			Parts[CurrentIndex]->Destroy();
			UnregisterPart(Parts[CurrentIndex], true);
		}
		else
		{
			CurrentIndex++;
		}
	}
	
	// Reconnect all valid connections
	for(AStructurePart* Part : Parts)
	{
		Part->AttachSlots();
	}
	
	// Update root distances
	for(AStructurePart* Part : Parts)
	{
		Part->ResetRootDistance();
	}
	RootPart->UpdateDistance(0);

	OnLayoutChanged.Broadcast();
}

float AStructure::GetUpkeep() const
{
	return Attributes->GetUpkeep() / (Attributes->GetUpkeepReduction() + 1);
}

bool AStructure::IsDetecting(AStructure* Other) const
{
	return (GetActorLocation() - Other->GetActorLocation()).SquaredLength() <= Attributes->GetSensorStrength() * Other->Attributes->GetSignatureVisibility();
}

UAbilitySystemComponent* AStructure::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FActiveGameplayEffectHandle AStructure::ApplyEffect(const TSubclassOf<UGameplayEffect> EffectClass)
{
	if(AbilitySystemComponent && EffectClass)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);

		if(SpecHandle.IsValid())
		{
			return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

	return FActiveGameplayEffectHandle();
}

FGameplayAbilitySpecHandle AStructure::GrantAbility(TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	if(HasAuthority() && AbilitySystemComponent && AbilityClass)
	{
		return AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, -1, this));
	}

	return FGameplayAbilitySpecHandle();
}

void AStructure::SetMoveInput(const FVector InInput)
{
	MoveInput = InInput.GetClampedToMaxSize(1);
}

void AStructure::SetRotateInput(const FVector InInput)
{
	RotateInput = InInput.GetClampedToMaxSize(1);
}

AFaction* AStructure::GetOwningFaction() const
{
	return OwningFaction;
}

void AStructure::SetOwningFaction(AFaction* InFaction)
{
	OwningFaction = InFaction;
}

USpringArmComponent* AStructure::GetCameraSpringArm() const
{
	return SpringArm;
}

FVector AStructure::CalculateImpulse(const FVector& RawVelocities, const FVector& RawInput, const float MaxSpeed, const float Accel, const float DeltaTime) const
{
	const FVector Velocities = GetTransform().InverseTransformVector(RawVelocities);
	const FVector ClampedInput = RawInput.GetClampedToMaxSize(1);
	const FVector Input = ClampedInput.IsNearlyZero(0.15) ? FVector::ZeroVector : ClampedInput;
	const FVector Diff = Input * MaxSpeed - Velocities;
	const FVector Applied = ClampVector(Diff, FVector(-Accel * DeltaTime), FVector(Accel * DeltaTime));
	return GetTransform().TransformVector(Applied);
}
