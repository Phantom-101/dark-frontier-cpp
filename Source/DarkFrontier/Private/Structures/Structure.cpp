// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"

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

void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(RootSection);
	
	UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	
	const float LinearMaxSpeed = Attributes->GetLinearMaxSpeed();
	const float LinearAccel = Attributes->GetLinearAcceleration();
	Mesh->AddImpulse(CalculateImpulse(Mesh->GetPhysicsLinearVelocity(), MoveInput, LinearMaxSpeed, LinearAccel, DeltaTime), NAME_None, true);

	const float AngularMaxSpeed = Attributes->GetAngularMaxSpeed();
	const float AngularAccel = Attributes->GetAngularAcceleration();
	// Possibly directly set velocity to zero once it's close enough
	Mesh->AddAngularImpulseInDegrees(CalculateImpulse(Mesh->GetPhysicsAngularVelocityInDegrees(), RotateAddInput + RotateOverrideInput, AngularMaxSpeed, AngularAccel, DeltaTime), NAME_None, true);

	UpdateCameraPosition();
}

void AStructure::InitRootSection(AStructureSection* NewRoot)
{
	if(RootSection == nullptr && NewRoot->OwningStructure == nullptr)
	{
		NewRoot->InitOwningStructure(this);
		RootSection = NewRoot;
		RootSection->SetActorRelativeLocation(FVector::ZeroVector);
		RootSection->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
}

AStructureSection* AStructure::GetRootSection()
{
	return RootSection;
}

void AStructure::RegisterSection(AStructureSection* Section)
{
	Section->SectionId = NextSectionId;
	NextSectionId++;
	Sections.Add(Section);
	UpdateAttributes();
}

void AStructure::UnregisterSection(AStructureSection* Section)
{
	Sections.Remove(Section);
	UpdateAttributes();
}

void AStructure::UpdateSections()
{
	// Called after a slot has been detached
	const TArray<AStructureSection*> ConnectedSections = GetConnectedSections();
	TArray<AStructureSection*> ToRemove;
	for(AStructureSection* Section : Sections)
	{
		if(!ConnectedSections.Contains(Section))
		{
			ToRemove.Add(Section);
			Section->Destroy();
		}
	}
	for(AStructureSection* Section : ToRemove)
	{
		UnregisterSection(Section);
	}
	// If no sections were removed, reconnect all valid connections
	for(AStructureSection* Section : ConnectedSections)
	{
		Section->AttachNearbySectionSlots();
	}
}

TArray<AStructureSection*> AStructure::GetCachedSections()
{
	// Implicitly copied
	return Sections;
}

TArray<AStructureSection*> AStructure::GetConnectedSections()
{
	TArray<AStructureSection*> Ret, Temp;
	Ret.Add(RootSection);
	Temp.Add(RootSection);
	while(Temp.Num() > 0)
	{
		for(const UStructureSectionSlot* Slot : Temp[0]->SectionSlots)
		{
			if(Slot->AttachedSlot != nullptr && !Ret.Contains(Slot->AttachedSlot->OwningSection))
			{
				Ret.Add(Slot->AttachedSlot->OwningSection);
				Temp.Add(Slot->AttachedSlot->OwningSection);
			}
		}
		Temp.RemoveAt(0);
	}
	return Ret;
}

bool AStructure::IsLayoutValid()
{
	return true;
}

UAbilitySystemComponent* AStructure::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AStructure::ApplyEffect(const TSubclassOf<UGameplayEffect> EffectClass)
{
	if(AbilitySystemComponent && EffectClass)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);

		if(SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AStructure::GrantAbility(TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	if(HasAuthority() && AbilitySystemComponent && AbilityClass)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, AbilityClass.GetDefaultObject()->InputID, this));
	}
}

bool AStructure::IsDetecting(AStructure* Other) const
{
	return (GetActorLocation() - Other->GetActorLocation()).SquaredLength() <= Attributes->GetSensorStrength() * Other->Attributes->GetSignatureVisibility();
}

void AStructure::Move(const FVector Value)
{
	MoveInput = Value.GetClampedToMaxSize(1);
}

void AStructure::RotateAdd(const FVector Value)
{
	RotateAddInput = (RotateAddInput + Value).GetClampedToMaxSize(1);
}

void AStructure::RotateOverride(const FVector Value)
{
	RotateOverrideInput = Value.GetClampedToMaxSize(1);
}

void AStructure::Look(const FVector2D Value)
{
}

void AStructure::SetCameraTarget(AActor* NewTarget)
{
	CameraTarget = NewTarget;
}

void AStructure::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UpdateAttributes();

	// Give any abilities here
}

void AStructure::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UpdateAttributes();
}

void AStructure::UpdateAttributes()
{
	ApplyEffect(DefaultAttributes);

	for(const AStructureSection* Section : Sections)
	{
		ApplyEffect(Section->AttributeEffect);
	}
}

FVector AStructure::CalculateImpulse(const FVector RawVelocities, const FVector RawInput, const float MaxSpeed, const float Accel, const float DeltaTime) const
{
	const FVector Velocities = GetTransform().InverseTransformVector(RawVelocities);
	const FVector ClampedInput = RawInput.GetClampedToMaxSize(1);
	const FVector Input = ClampedInput.IsNearlyZero(0.15) ? FVector::ZeroVector : ClampedInput;
	const FVector Diff = Input * MaxSpeed - Velocities;
	const FVector Applied = ClampVector(Diff, FVector(-Accel * DeltaTime), FVector(Accel * DeltaTime));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Input: %s"), *Input.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Velocities: %s"), *Velocities.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Diff: %s"), *Diff.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Applied: %s"), *Applied.ToString()));
	return GetTransform().TransformVector(Applied);
}

void AStructure::UpdateCameraPosition()
{
	if(!CameraTarget)
	{
		SetCameraTarget(this);
	}

	FVector Origin, Extent;
	CameraTarget->GetActorBounds(false, Origin, Extent, true);
	const double SafeRadius = Extent.Length();
	// todo do not assume target actor location is in world space
	SpringArm->SetRelativeLocation(GetTransform().InverseTransformPosition(CameraTarget->GetActorLocation()));
	SpringArm->TargetArmLength = SafeRadius * 1.5;
}
