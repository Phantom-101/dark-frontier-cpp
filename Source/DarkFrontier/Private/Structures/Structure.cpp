// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"

#include "Log.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/GameUI/StructurePartAbilityClass.h"

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

	if(!IsValid(RootPart)) return;
	
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

bool AStructure::TryInit(AStructurePart* NewRoot, const bool RegisterOnly)
{
	if(RootPart) return false;
	if(NewRoot->GetOwningStructure()) return false;
	
	NewRoot->TryInit(this, RegisterOnly);
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

AStructurePart* AStructure::GetPart(const FString InId)
{
	for(AStructurePart* Part : Parts)
	{
		if(Part->GetPartId().Equals(InId))
		{
			return Part;
		}
	}
	return nullptr;
}

void AStructure::RegisterPart(AStructurePart* InPart, const bool SuppressEvent, bool KeepId)
{
	if(!KeepId)
	{
		InPart->TryInitPartId(FGuid::NewGuid().ToString());
	}
	
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

bool AStructure::LoadLayout(FStructureLayout InLayout)
{
	if(RootPart) return false;

	// If any layout part has an empty id, set it to a random guid
	for(int i = 0; i < InLayout.Parts.Num(); i++)
	{
		if(InLayout.Parts[i].PartId.IsEmpty())
		{
			InLayout.Parts[i].PartId = FGuid::NewGuid().ToString();
		}
	}
	
	// Assume first part data is for the root part
	for(FStructureLayoutPart PartData : InLayout.Parts)
	{
		if(PartData.IsValid())
		{
			AStructurePart* Part = GetWorld()->SpawnActor<AStructurePart>(PartData.PartClass);
			
			if(RootPart)
			{
				if(!Part->TryInit(this, true))
				{
					UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to create layout part on %s with id %s"), *GetName(), *PartData.PartId);
				}
			}
			else
			{
				if(!TryInit(Part, true))
				{
					UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to create layout part as root on %s with id %s"), *GetName(), *PartData.PartId);
				}
			}
			
			if(!Part->TryInitPartId(PartData.PartId))
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to set layout part on %s to target id %s"), *GetName(), *PartData.PartId);
			}
		}
		else
		{
			// All layout part ids are valid as any empty ids were set to random guids by this point
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout part on %s with invalid class"), *GetName());
		}
	}

	if(!RootPart) return false;

	for(FStructureLayoutConnection ConnectionData : InLayout.Connections)
	{
		if(ConnectionData.IsValid())
		{
			AStructurePart* PartA = GetPart(ConnectionData.PartAId);
			AStructurePart* PartB = GetPart(ConnectionData.PartBId);

			if(IsValid(PartA) && IsValid(PartB))
			{
				UStructurePartSlot* SlotA = PartA->GetSlot(ConnectionData.PartASlot);
				UStructurePartSlot* SlotB = PartB->GetSlot(ConnectionData.PartBSlot);

				if(IsValid(SlotA) && IsValid(SlotB))
				{
					// Suppress layout update to prevent deletion of parts not yet connected via connections
					if(!SlotA->TryAttach(SlotB, true))
					{
						UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to create layout connection on %s between %s (%s), %s (%s)"), *GetName(), *ConnectionData.PartAId, *ConnectionData.PartASlot.ToString(), *ConnectionData.PartBId, *ConnectionData.PartBSlot.ToString());
					}
				}
				else
				{
					UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with missing/invalid slots(s)"), *GetName());
				}
			}
			else
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with missing/invalid part(s)"), *GetName());
			}
		}
		else
		{
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with unset ids"), *GetName());
		}
	}

	// All parts should be connected at this point
	UpdateLayoutInformation();

	return true;
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
			if(IsValid(Slot->GetAttachedSlot()) && !NewParts.Contains(Slot->GetAttachedSlot()->GetOwningPart()))
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

void AStructure::ActivateAbility(const UStructurePartAbilityClass* AbilityClassObj)
{
	if(AbilityClassObj->TargetStructure != this)
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Tried activating ability %s on incorrect structure"), *AbilityClassObj->AbilityClass->GetDisplayNameText().ToString());
		return;
	}
	
	for(AStructurePart* Part : Parts)
	{
		if(Part->GetClass() == AbilityClassObj->PartClass)
		{
			Part->ActivateAbility(AbilityClassObj->AbilityClass);
		}
	}
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

FGameplayAbilitySpecHandle AStructure::GiveAbility(TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	if(HasAuthority() && AbilitySystemComponent && AbilityClass)
	{
		return AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, AbilitySystemComponent));
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
