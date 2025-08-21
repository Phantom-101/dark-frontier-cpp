// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePart.h"
#include "GameplayEffect.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Gameplay/Attributes/HullAttributeSet.h"
#include "Libraries/GameplayFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureProduction.h"
#include "Structures/StructureSlot.h"

AStructurePart::AStructurePart()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStructurePart::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UStructureSlot>(Slots);
	GetComponents<UStructureFacility>(Facilities);
}

void AStructurePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// stuff here
}

FText AStructurePart::GetTypeName() const
{
	return TypeName;
}

void AStructurePart::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = PartTags;
}

TSubclassOf<UGameplayEffect> AStructurePart::GetPassiveEffect() const
{
	return PassiveEffect;
}

void AStructurePart::OnAdded(AStructure* Structure)
{
	OwningStructure = Structure;

	TryInitPartId(FGuid::NewGuid().ToString());

	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);

	if(PassiveEffect)
	{
		PassiveEffectHandle = OwningStructure->GetGameplay()->ApplyEffect(PassiveEffect);

		UGameplayEffect* Effect = PassiveEffect->GetDefaultObject<UGameplayEffect>();
		const float Hull = UGameplayFunctionLibrary::Aggregate(Effect, UHullAttributeSet::GetMaxHullAttribute(), EGameplayModOp::Type::Additive);

		// Add the extra hull that this part provides
		UStructureGameplay* Gameplay = OwningStructure->GetGameplay();
		Gameplay->SetHull(Gameplay->GetHull() + Hull);
	}
}

void AStructurePart::OnRemoved()
{
	if(PassiveEffectHandle.IsValid())
	{
		OwningStructure->GetGameplay()->RemoveEffect(PassiveEffectHandle);
		PassiveEffectHandle = FActiveGameplayEffectHandle();

		// Clamp hull to the now reduced max hull
		UStructureGameplay* Gameplay = OwningStructure->GetGameplay();
		Gameplay->SetHull(Gameplay->GetHull());
	}
}

AStructure* AStructurePart::GetOwningStructure() const
{
	return OwningStructure;
}

bool AStructurePart::IsRootPart() const
{
	return IsValid(OwningStructure) && OwningStructure->GetLayout()->GetRootPart() == this;
}

FString AStructurePart::GetPartId() const
{
	return PartId;
}

bool AStructurePart::TryInitPartId(FString InId)
{
	if(!PartId.IsEmpty()) return false;
	PartId = InId;
	return true;
}

TArray<UStructureSlot*> AStructurePart::GetSlots()
{
	return Slots;
}

TArray<UStructureSlot*> AStructurePart::GetCompatibleSlots(const UStructureSlot* Other)
{
	TArray<UStructureSlot*> Ret;
	Ret.Reserve(Slots.Num());
	for(UStructureSlot* Slot : Slots)
	{
		if(Slot->CanAttach(Other)) Ret.Add(Slot);
	}
	return Ret;
}

UStructureSlot* AStructurePart::GetSlot(const FText InName)
{
	for(UStructureSlot* Slot : Slots)
	{
		if(Slot->GetSlotName().EqualTo(InName))
		{
			return Slot;
		}
	}
	
	return nullptr;
}

void AStructurePart::AttachSlots()
{
	for(UStructureSlot* Slot : Slots)
	{
		if(Slot->GetAttachedSlot() != nullptr)
		{
			continue;
		}
		
		for(UStructureSlot* Other : OwningStructure->GetLayout()->GetSlots())
		{
			if(Other->GetOwningPart() == this)
			{
				continue;
			}
			
			if((Other->GetComponentLocation() - Slot->GetComponentLocation()).IsNearlyZero(1))
			{
				Slot->TryAttach(Other);
			}
		}
	}
}

void AStructurePart::DetachSlots()
{
	for(UStructureSlot* Slot : Slots)
	{
		Slot->TryDetach();
	}
	OwningStructure->GetLayout()->RemoveUnconnected();
}

TArray<UStructureFacility*> AStructurePart::GetFacilities()
{
	return Facilities;
}

float AStructurePart::GetPartMaxHealth() const
{
	return PartMaxHealth;
}

float AStructurePart::GetPartHealth() const
{
	return PartHealth;
}

void AStructurePart::SetPartHealth(const float Target)
{
	PartHealth = FMath::Clamp(Target, 0, PartMaxHealth);
}

float AStructurePart::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Owning structure will calculate the part damage and apply it via setters
	return OwningStructure->PropagateDamage(this, DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

TArray<const UStructureSlot*> AStructurePart::GetSlots_CDO(const TSubclassOf<AStructurePart>& PartClass)
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(PartClass);
	if(BPClass == nullptr) return TArray<const UStructureSlot*>();

	TArray<const UStructureSlot*> Slots;
	const TArray<USCS_Node*>& Nodes = BPClass->SimpleConstructionScript->GetAllNodes();
	for(const USCS_Node* Node : Nodes)
	{
		if(Node->ComponentClass == UStructureSlot::StaticClass())
		{
			Slots.Add(Cast<UStructureSlot>(Node->ComponentTemplate));
		}
	}
	return Slots;
}

TArray<const UStructureSlot*> AStructurePart::GetCompatibleSlots_CDO(const TSubclassOf<AStructurePart>& PartClass, const UStructureSlot* Other)
{
	TArray<const UStructureSlot*> CDOSlots = GetSlots_CDO(PartClass);
	TArray<const UStructureSlot*> Ret;
	Ret.Reserve(CDOSlots.Num());
	for(const UStructureSlot* Slot : CDOSlots)
	{
		if(Slot->CanAttach(Other)) Ret.Add(Slot);
	}
	return Ret;
}

const UStructureSlot* AStructurePart::GetSlot_CDO(const TSubclassOf<AStructurePart>& PartClass, const FText& InName)
{
	for(const UStructureSlot* Slot : GetSlots_CDO(PartClass))
	{
		if(Slot->GetSlotName().EqualTo(InName))
		{
			return Slot;
		}
	}
	
	return nullptr;
}
