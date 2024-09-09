// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Log.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Inventory.h"
#include "Sectors/Sector.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureDamage.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAuthoring.h"
#include "Structures/StructureDock.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureIndices.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "Structures/StructureValidationResult.h"
#include "Structures/Damage/StructureDamageType.h"
#include "Structures/Indications/DistanceIndication.h"
#include "Structures/Indications/HullIndication.h"
#include "Structures/Indications/SpeedIndication.h"
#include "Structures/Indications/StructureIndication.h"

AStructure::AStructure()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	SpringArm->SetupAttachment(StaticMesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Indices = UStructureIndices::CreateIndices(this);

	Inventory = CreateDefaultSubobject<UInventory>("Inventory");

	Gameplay = UStructureGameplay::CreateGameplay(this);
}

void AStructure::PostInitializeComponents()
{
	Gameplay->Initialize();
	
	Super::PostInitializeComponents();
}

void AStructure::BeginPlay()
{
	Super::BeginPlay();

	Gameplay->Initialize();
	Gameplay->ApplyStartingEffects();

	TryEnterSector(CurrentSector);

	AddIndication(HullIndicationClass.Get());
	AddIndication(DistanceIndicationClass.Get());
	AddIndication(SpeedIndicationClass.Get());

	UStructureAuthoring* Authoring = GetComponentByClass<UStructureAuthoring>();
	if(Authoring != nullptr)
	{
		LoadLayout(Authoring->GetLayout());
	}
}

void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsValid(Indices->GetRootPart())) return;

	UpdateTickLevel();

	const UStructureAttributeSet* AttributeSet = Gameplay->GetAttributeSet();

	if(TickLevel == EStructureTickLevel::Full)
	{
		const float LinearMaxSpeed = AttributeSet->GetLinearMaxSpeed();
		const float LinearAccel = AttributeSet->GetLinearAcceleration();
		StaticMesh->AddImpulse(CalculateImpulse(StaticMesh->GetPhysicsLinearVelocity(), MoveInput, LinearMaxSpeed, LinearAccel, DeltaTime), NAME_None, true);

		const float AngularMaxSpeed = AttributeSet->GetAngularMaxSpeed();
		const float AngularAccel = AttributeSet->GetAngularAcceleration();
		StaticMesh->AddAngularImpulseInDegrees(CalculateImpulse(StaticMesh->GetPhysicsAngularVelocityInDegrees(), RotateInput, AngularMaxSpeed, AngularAccel, DeltaTime), NAME_None, true);
	}
	else if(TickLevel == EStructureTickLevel::Limited)
	{
		const FVector ScaledMoveInput = MoveInput * AttributeSet->GetLinearMaxSpeed();
		SetActorLocation(GetActorLocation() + ScaledMoveInput);

		const FVector ScaledRotateInput = RotateInput * AttributeSet->GetAngularMaxSpeed();
		const FRotator Rotation = FRotator(ScaledRotateInput.X, ScaledRotateInput.Z, ScaledRotateInput.Y);
		SetActorRotation(GetActorRotation() + Rotation);
	}
}

void AStructure::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Gameplay->Initialize();
	
	SetOwner(NewController); // For ASC mixed replication mode
}

bool AStructure::TryDestroy()
{
	if(!IsValid(Indices->GetRootPart())) return false;
	
	Indices->GetRootPart()->DetachSlots();
	UpdateLayoutInformation();

	Indices->GetRootPart()->Destroy();

	if(IsValid(CurrentSector))
	{
		CurrentSector->UnregisterStructure(this);
	}

	Destroy();

	return true;
}

UStructureIndices* AStructure::GetIndices() const
{
	return Indices;
}

EStructureValidationResult AStructure::ValidateLayout()
{
	TArray<AStructurePart*> Parts = Indices->GetParts();
	for(int i = 0; i < Parts.Num(); i++)
	{
		for(int j = i + 1; j < Parts.Num(); j++)
		{
			if(Parts[i]->IsOverlappingActor(Parts[j]))
			{
				return EStructureValidationResult::SelfIntersecting;
			}
		}
	}
	
	if(Gameplay->GetUpkeep() > Gameplay->GetAttributeSet()->GetMaxUpkeep())
	{
		return EStructureValidationResult::UpkeepExceeded;
	}

	return EStructureValidationResult::Valid;
}

bool AStructure::LoadLayout(FStructureLayout InLayout)
{
	if(Indices->GetRootPart()) return false;

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
			AStructurePart* Part = GetWorld()->SpawnActor<AStructurePart>(PartData.PartType);

			if(!Part->TryInitPartId(PartData.PartId))
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to set layout part on %s to target id %s"), *GetName(), *PartData.PartId);
			}
			
			if(!Indices->AddPart(Part))
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to create layout part on %s with id %s"), *GetName(), *PartData.PartId);
			}
		}
		else
		{
			// All layout part ids are valid as any empty ids were set to random guids by this point
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout part on %s with invalid class"), *GetName());
		}
	}

	if(!Indices->GetRootPart()) return false;

	for(FStructureLayoutConnection ConnectionData : InLayout.Connections)
	{
		if(ConnectionData.IsValid())
		{
			AStructurePart* PartA = Indices->GetPart(ConnectionData.PartAId);
			AStructurePart* PartB = Indices->GetPart(ConnectionData.PartBId);

			if(IsValid(PartA) && IsValid(PartB))
			{
				UStructureSlot* SlotA = PartA->GetSlot(ConnectionData.PartASlot);
				UStructureSlot* SlotB = PartB->GetSlot(ConnectionData.PartBSlot);

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
	NewParts.Add(Indices->GetRootPart());

	int CurrentIndex = 0;
	while(CurrentIndex < NewParts.Num())
	{
		for(const UStructureSlot* Slot : NewParts[CurrentIndex]->GetSlots())
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
		if(!Indices->GetParts().Contains(Part))
		{
			Indices->AddPart(Part);
		}
	}

	CurrentIndex = 0;
	TArray<AStructurePart*> Parts = Indices->GetParts();
	while(CurrentIndex < Parts.Num())
	{
		if(!NewParts.Contains(Parts[CurrentIndex]))
		{
			Parts[CurrentIndex]->Destroy();
			Indices->RemovePart(Parts[CurrentIndex]);
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
	
	OnLayoutChanged.Broadcast();
}

UStructureDock* AStructure::GetDock() const
{
	return CurrentDock;
}

bool AStructure::TryDock(UStructureDock* InDock)
{
	if(InDock->ConfirmDock(this))
	{
		CurrentDock = InDock;
		AttachToActor(CurrentDock->GetOwner(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		return true;
	}

	return false;
}

bool AStructure::TryUnDock()
{
	if(CurrentDock->ConfirmUnDock(this))
	{
		CurrentDock = nullptr;
		DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		return true;
	}

	return false;
}

EStructureTickLevel AStructure::GetTickLevel()
{
	return TickLevel;
}

bool AStructure::SetTickLevel(EStructureTickLevel InLevel)
{
	if(TickLevel == InLevel) return false;

	TickLevel = InLevel;

	// Set visibility and collision
	if(TickLevel == EStructureTickLevel::Full)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}

	return true;
}

void AStructure::UpdateTickLevel()
{
	const AStructure* Player = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(IsValid(Player))
	{
		if(CurrentSector == Player->CurrentSector)
		{
			SetTickLevel(EStructureTickLevel::Full);
		}
		else
		{
			SetTickLevel(EStructureTickLevel::Limited);
		}
	}
	else
	{
		SetTickLevel(EStructureTickLevel::Omitted);
	}
}

bool AStructure::TryEnterSector(ASector* InSector)
{
	if(!IsValid(InSector) || CurrentSector == InSector) return false;

	if(IsValid(CurrentSector))
	{
		CurrentSector->UnregisterStructure(this);
	}

	CurrentSector = InSector;
	CurrentSector->RegisterStructure(this);

	UpdateTickLevel();
	
	return true;
}

UInventory* AStructure::GetInventory() const
{
	return Inventory;
}

AFaction* AStructure::GetOwningFaction() const
{
	return OwningFaction;
}

void AStructure::SetOwningFaction(AFaction* InFaction)
{
	OwningFaction = InFaction;
}

AStructure* AStructure::GetTarget() const
{
	return Target;
}

void AStructure::SetTarget(AStructure* InTarget)
{
	Target = InTarget;
}

UStructureGameplay* AStructure::GetGameplay() const
{
	return Gameplay;
}

UAbilitySystemComponent* AStructure::GetAbilitySystemComponent() const
{
	return Gameplay->GetAbilitySystemComponent();
}

void AStructure::ApplyDamage(FStructureDamage Damage, AStructurePart* HitPart, FVector HitLocation)
{
	const UStructureAbilitySystemComponent* AbilitySystemComponent = Gameplay->GetAbilitySystemComponent();
	
	if(Damage.IsValid() && Gameplay->GetShield() > 0)
	{
		const float PostMitigation = Damage.Amount * Damage.DamageType.GetDefaultObject()->GetShieldMultiplier(AbilitySystemComponent);
		const float AbsorbedPercent = FMath::Min(Gameplay->GetShield() / PostMitigation, 1);
		const float Applied = PostMitigation * AbsorbedPercent;
		Gameplay->SetShield(Gameplay->GetShield() - Applied);
		Damage = FStructureDamage(Damage.DamageType, Damage.Amount * (1 - AbsorbedPercent));

		FGameplayCueParameters Parameters;
		Parameters.Location = HitLocation;
		Parameters.RawMagnitude = Applied;
		AbilitySystemComponent->ExecuteGameplayCueLocal(ShieldDamageCueTag, Parameters);
	}

	if(Damage.IsValid() && Gameplay->GetHull() > 0)
	{
		const float PostMitigation = Damage.Amount * Damage.DamageType.GetDefaultObject()->GetHullMultiplier(AbilitySystemComponent);
		Gameplay->SetHull(Gameplay->GetHull() - PostMitigation);

		FGameplayCueParameters Parameters;
		Parameters.Location = HitLocation;
		Parameters.RawMagnitude = PostMitigation;
		AbilitySystemComponent->ExecuteGameplayCueLocal(HullDamageCueTag, Parameters);
	}
}

TArray<UStructureIndication*> AStructure::GetIndications()
{
	return Indications;
}

UStructureIndication* AStructure::AddIndication(TSubclassOf<UStructureIndication> IndicationClass)
{
	UStructureIndication* Indication = NewObject<UStructureIndication>(this, IndicationClass);
	Indication->TryInit(this);
	
	Indications.Add(Indication);
	OnIndicationAdded.Broadcast(Indication);
	
	return Indication;
}

void AStructure::RemoveIndication(UStructureIndication* Indication)
{
	if(Indications.Contains(Indication))
	{
		Indications.Remove(Indication);
		OnIndicationRemoved.Broadcast(Indication);
	}
}

void AStructure::SetMoveInput(const FVector InInput)
{
	MoveInput = InInput.GetClampedToMaxSize(1);
}

void AStructure::SetRotateInput(const FVector InInput)
{
	RotateInput = InInput.GetClampedToMaxSize(1);
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
