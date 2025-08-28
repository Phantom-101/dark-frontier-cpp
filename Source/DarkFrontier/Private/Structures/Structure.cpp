// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Macros.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAuthoring.h"
#include "Structures/StructureDamageType.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureLocation.h"
#include "Structures/StructurePart.h"
#include "Structures/Indications/DistanceIndication.h"
#include "Structures/Indications/HullIndication.h"
#include "Structures/Indications/SpeedIndication.h"
#include "Structures/Indications/StructureIndication.h"
#include "UI/Screens/Flight/Selectors/StructureSelector.h"

AStructure::AStructure()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	SpringArm->SetupAttachment(StaticMesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Layout = UStructureLayout::CreateLayout(this);
	Location = UStructureLocation::CreateLocation(this);
	Inventory = UStructureInventory::CreateInventory(this);
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

	OnTakePointDamage.AddDynamic(this, &AStructure::HandlePointDamage);

	Location->EnterSector(InitialSector);

	AddIndication(UHullIndication::StaticClass());
	AddIndication(UDistanceIndication::StaticClass());
	AddIndication(USpeedIndication::StaticClass());

	const UStructureAuthoring* Authoring = GetComponentByClass<UStructureAuthoring>();
	if(Authoring != nullptr)
	{
		Layout->LoadData(Authoring->GetLayoutData());
	}
}

void AStructure::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsValid(Layout->GetRootPart())) return;

	UpdateTickLevel();

	if(TickLevel == EStructureTickLevel::Full)
	{
		const float LinearMaxSpeed = Gameplay->GetLinearMaxSpeed();
		const float LinearAccel = Gameplay->GetLinearAcceleration();
		StaticMesh->AddImpulse(CalculateImpulse(StaticMesh->GetPhysicsLinearVelocity(), MoveInput, LinearMaxSpeed, LinearAccel, DeltaTime), NAME_None, true);

		const float AngularMaxSpeed = Gameplay->GetAngularMaxSpeed();
		const float AngularAccel = Gameplay->GetAngularAcceleration();
		StaticMesh->AddAngularImpulseInDegrees(CalculateImpulse(StaticMesh->GetPhysicsAngularVelocityInDegrees(), RotateInput, AngularMaxSpeed, AngularAccel, DeltaTime), NAME_None, true);
	}
	else if(TickLevel == EStructureTickLevel::Limited)
	{
		const FVector ScaledMoveInput = MoveInput * Gameplay->GetLinearMaxSpeed();
		SetActorLocation(GetActorLocation() + ScaledMoveInput);

		const FVector ScaledRotateInput = RotateInput * Gameplay->GetAngularMaxSpeed();
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
	if(!IsValid(Layout->GetRootPart())) return false;
	
	Layout->RemoveAll();
	Location->ExitSector();
	Destroy();

	return true;
}

UStructureLayout* AStructure::GetLayout() const
{
	return Layout;
}

UStructureLocation* AStructure::GetLocation() const
{
	return Location;
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
		if(Location->GetSector() == Player->GetLocation()->GetSector())
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

UStructureInventory* AStructure::GetInventory() const
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

bool AStructure::IsPlayer() const
{
	return this == UGameFunctionLibrary::GetPlayerStructure(this);
}

bool AStructure::IsTargetable(AStructure* Structure) const
{
	// TODO check detection
	return Structure->Location->GetSector() == Location->GetSector();
}

TSubclassOf<USelector> AStructure::GetSelectorClass() const
{
	return SelectorClass.Get();
}

UStructureGameplay* AStructure::GetGameplay() const
{
	return Gameplay;
}

UAbilitySystemComponent* AStructure::GetAbilitySystemComponent() const
{
	return Gameplay->GetAbilitySystemComponent();
}

float AStructure::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// This function should not be called as all damage should be routed through structure parts first 
	return PropagateDamage(nullptr, DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

float AStructure::PropagateDamage(AStructurePart* Part, float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	// Calculate damage based on damage event type and fire event dispatchers
	// The value provided to event listeners is the raw damage before multipliers are applied
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GUARD_RETURN(DamageAmount >= 0, 0);
	
	const UStructureDamageType* DamageType = UStructureDamageType::GetDamageTypeFromEvent(DamageEvent);

	const float ShieldEquivalent = Gameplay->GetShield() / DamageType->ShieldMultiplier;
	const float ShieldAbsorbed = FMath::Min(DamageAmount, ShieldEquivalent);
	const float ShieldDamage = ShieldAbsorbed * DamageType->ShieldMultiplier;
	
	Gameplay->SetShield(Gameplay->GetShield() - ShieldDamage);
	DamageAmount -= ShieldAbsorbed;

	const float HullEquivalent = Gameplay->GetShield() / DamageType->HullMultiplier;
	const float HullAbsorbed = FMath::Min(DamageAmount, HullEquivalent);
	const float HullDamage = HullAbsorbed * DamageType->HullMultiplier;
	
	Gameplay->SetHull(Gameplay->GetHull() - HullDamage);

	if(IsValid(Part))
	{
		const float PartDamage = HullAbsorbed * DamageType->PartMultiplier;
		Part->SetPartHealth(Part->GetPartHealth() - PartDamage);
	}
	
	// Return the actual amount absorbed
	return ShieldAbsorbed + HullAbsorbed;
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

UStaticMeshComponent* AStructure::GetStaticMesh() const
{
	return StaticMesh;
}

USpringArmComponent* AStructure::GetCameraSpringArm() const
{
	return SpringArm;
}

void AStructure::SetActorHiddenInGame(const bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
	for(AStructurePart* Part : Layout->GetParts())
	{
		Part->SetActorHiddenInGame(bNewHidden);
	}
}

FVector AStructure::CalculateImpulse(const FVector& RawVelocities, const FVector& RawInput, const float MaxSpeed, const float Accel, const float DeltaTime) const
{
	const FVector Velocities = GetTransform().InverseTransformVector(RawVelocities);
	const FVector Input = RawInput.GetClampedToMaxSize(1);
	const FVector Diff = Input * MaxSpeed - Velocities;
	const FVector Applied = ClampVector(Diff, FVector(-Accel * DeltaTime), FVector(Accel * DeltaTime));
	return GetTransform().TransformVector(Applied);
}

void AStructure::HandlePointDamage(AActor* DamagedActor, const float Damage, AController* InstigatedBy, const FVector HitLocation, UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if(Damage > 0)
	{
		FGameplayCueParameters Parameters;
		Parameters.Location = HitLocation;
		Parameters.RawMagnitude = Damage;
		Gameplay->GetAbilitySystemComponent()->ExecuteGameplayCueLocal(HullDamageCueTag, Parameters);
	}
}
