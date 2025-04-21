// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Inventory.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAuthoring.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureLocation.h"
#include "Structures/StructurePart.h"
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

	Layout = UStructureLayout::CreateLayout(this);
	Location = UStructureLocation::CreateLocation(this);
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

bool AStructure::IsPlayer() const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController == nullptr)
	{
		return false;
	}

	return PlayerController->GetPawn() == this;
}

bool AStructure::IsSelected() const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController == nullptr)
	{
		return false;
	}

	const AStructure* Player = Cast<AStructure>(PlayerController->GetPawn());
	if(Player == nullptr)
	{
		return false;
	}

	return Player->Target == this;
}

UStructureGameplay* AStructure::GetGameplay() const
{
	return Gameplay;
}

UAbilitySystemComponent* AStructure::GetAbilitySystemComponent() const
{
	return Gameplay->GetAbilitySystemComponent();
}

UTargetGroup* AStructure::GetTargetGroup() const
{
	return HullTargetGroup;
}

float AStructure::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Calculate damage based on damage event type and fire event dispatchers
	// The value provided to event listeners is the raw damage before resistances are applied
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	const UDamageType* DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass.GetDefaultObject() : GetDefault<UDamageType>();
	const UStructureDamageType* StructureDamageType = Cast<UStructureDamageType>(DamageType);

	// Healing is not supported
	if(DamageAmount > 0)
	{
		const float Multiplier = StructureDamageType ? StructureDamageType->Evaluate(HullTargetGroup, GetAbilitySystemComponent()) : 1;
		const float Equivalent = Gameplay->GetHull() / Multiplier;
		const float Absorbed = FMath::Min(DamageAmount, Equivalent);
		const float Damage = Absorbed * Multiplier;
		
		Gameplay->SetHull(Gameplay->GetHull() - Damage);
		
		// Return the actual amount absorbed
		return Absorbed;
	}

	return 0;
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
