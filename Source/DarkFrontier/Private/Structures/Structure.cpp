// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Structure.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartAction.h"
#include "Structures/StructurePartActionGroup.h"
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
	
	ApplyEffect(DefaultAttributes);
	ApplyEffect(RegenEffect);
}

void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(RootPart);
	
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

void AStructure::InitRootPart(AStructurePart* NewRoot)
{
	if(RootPart == nullptr && NewRoot->OwningStructure == nullptr)
	{
		NewRoot->InitOwningStructure(this);
		RootPart = NewRoot;
		RootPart->SetActorRelativeLocation(FVector::ZeroVector);
		RootPart->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
}

AStructurePart* AStructure::GetRootPart()
{
	return RootPart;
}

void AStructure::RegisterPart(AStructurePart* InPart)
{
	InPart->PartId = NextPartId;
	NextPartId++;
	CachedParts.Add(InPart);
	InPart->OnRegistered();
	if(OnLayoutChanged.IsBound())
	{
		OnLayoutChanged.Execute();
	}
}

void AStructure::UnregisterPart(AStructurePart* InPart)
{
	CachedParts.Remove(InPart);
	InPart->OnUnregistered();
	if(OnLayoutChanged.IsBound())
	{
		OnLayoutChanged.Execute();
	}
}

UStructurePartAction* AStructure::RegisterAction(TSubclassOf<UStructurePartActionGroup> GroupType, TSubclassOf<UStructurePartAction> ActionType)
{
	UStructurePartAction* Action = NewObject<UStructurePartAction>(this, ActionType);
	for(UStructurePartActionGroup* Group : ActionGroups)
	{
		if(Group->GetClass() == GroupType)
		{
			Group->Actions.Add(Action);
			if(OnActionsChanged.IsBound())
			{
				OnActionsChanged.Execute();
			}
			return Action;
		}
	}
	UStructurePartActionGroup* Group = NewObject<UStructurePartActionGroup>(this, GroupType);
	ActionGroups.Add(Group);
	Group->Actions.Add(Action);
	if(OnActionsChanged.IsBound())
	{
		OnActionsChanged.Execute();
	}
	return Action;
}

void AStructure::UnregisterAction(TSubclassOf<UStructurePartActionGroup> GroupType, UStructurePartAction* InAction)
{
	for(UStructurePartActionGroup* Group : ActionGroups)
	{
		if(Group->GetClass() == GroupType)
		{
			Group->Actions.Remove(InAction);
			if(OnActionsChanged.IsBound())
			{
				OnActionsChanged.Execute();
			}
			return;
		}
	}
}

TArray<UStructurePartActionGroup*> AStructure::GetActionGroups()
{
	// Implicitly copied
	return ActionGroups;
}

TArray<AStructurePart*> AStructure::GetCachedParts()
{
	// Implicitly copied
	return CachedParts;
}

void AStructure::UpdateCachedParts()
{
	// Called after a slot has been detached
	const TArray<AStructurePart*> ConnectedParts = GetConnectedParts();
	// Checking connected unregistered parts is not necessary but this exists just in case
	TArray<AStructurePart*> ToAdd, ToRemove;
	for(AStructurePart* Part : CachedParts)
	{
		if(!CachedParts.Contains(Part))
		{
			ToAdd.Add(Part);
		}
		if(!ConnectedParts.Contains(Part))
		{
			ToRemove.Add(Part);
			Part->Destroy();
		}
	}
	for(AStructurePart* Part : ToAdd)
	{
		RegisterPart(Part);
	}
	for(AStructurePart* Part : ToRemove)
	{
		UnregisterPart(Part);
	}
	// If no sections were removed, reconnect all valid connections
	for(AStructurePart* Part : ConnectedParts)
	{
		Part->AttachNearbyPartSlots();
	}
}

TArray<AStructurePart*> AStructure::GetConnectedParts() const
{
	TArray<AStructurePart*> Ret, Temp;
	Ret.Add(RootPart);
	Temp.Add(RootPart);
	while(Temp.Num() > 0)
	{
		for(const UStructurePartSlot* Slot : Temp[0]->PartSlots)
		{
			if(Slot->AttachedSlot != nullptr && !Ret.Contains(Slot->AttachedSlot->OwningPart))
			{
				Ret.Add(Slot->AttachedSlot->OwningPart);
				Temp.Add(Slot->AttachedSlot->OwningPart);
			}
		}
		Temp.RemoveAt(0);
	}
	return Ret;
}

bool AStructure::IsPartLayoutValid()
{
	for(int i = 0; i < CachedParts.Num(); i++)
	{
		for(int j = i + 1; j < CachedParts.Num(); j++)
		{
			if(CachedParts[i]->IsOverlappingActor(CachedParts[j]))
			{
				return false;
			}
		}
	}
	return true;
}

void AStructure::UpdatePartDistances()
{
	for(AStructurePart* Part : CachedParts)
	{
		Part->DistanceToRoot = -1;
	}
	RootPart->PropagateDistanceUpdate(0);
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
	LookRotation = FVector2D(FMath::Fmod(LookRotation.X + Value.X, 360), FMath::Clamp(LookRotation.Y + Value.Y, -90, 90));
}

void AStructure::Zoom(const float Value)
{
	ZoomLevel = FMath::Clamp(ZoomLevel + Value, 1.5, 10);
}

void AStructure::SetCameraTarget(AActor* NewTarget)
{
	CameraTarget = NewTarget;
}

void AStructure::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// Give any abilities here
}

void AStructure::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
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

	FBoxSphereBounds Bounds;
	if(const AStructure* TargetStructure = Cast<AStructure>(CameraTarget))
	{
		Bounds = TargetStructure->GetStructureBounds(true);
	}
	else
	{
		Bounds = GetBounds(CameraTarget, true);
	}
	// todo do not assume target actor location is in world space
	SpringArm->SetRelativeLocation(GetTransform().InverseTransformPosition(CameraTarget->GetActorLocation()));
	SpringArm->TargetArmLength = Bounds.SphereRadius * 2 * ZoomLevel;

	SpringArm->SetWorldRotation(CameraTarget->GetActorRotation());
	SpringArm->AddLocalRotation(FRotator(LookRotation.Y, LookRotation.X, 0));
}

FBoxSphereBounds AStructure::GetStructureBounds(const bool OnlyCollidingComponents) const
{
	FBoxSphereBounds Bounds;
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (const AActor* AttachedActor : AttachedActors)
	{
		Bounds = Bounds + GetBounds(AttachedActor, OnlyCollidingComponents);
	}
	return Bounds;
}

FBoxSphereBounds AStructure::GetBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds;
	Actor->ForEachComponent<UPrimitiveComponent>(false, [&](const UPrimitiveComponent* InPrimComp)
	{
		if (InPrimComp->IsRegistered() && (!OnlyCollidingComponents || InPrimComp->IsCollisionEnabled()))
		{
			Bounds = Bounds + InPrimComp->Bounds;
		}
	});
	return Bounds;
}
