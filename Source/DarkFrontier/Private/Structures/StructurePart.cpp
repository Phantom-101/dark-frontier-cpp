// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePart.h"
#include "GameplayEffect.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Structures/Structure.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureDamage.h"
#include "Structures/StructureDock.h"
#include "Structures/StructureFacility.h"
#include "Structures/StructureSlot.h"

AStructurePart::AStructurePart()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStructurePart::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UStructureSlot>(Slots);
	GetComponents<UStructureDock>(Docks);
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

UStructurePartGroup* AStructurePart::GetPartType() const
{
	return PartType;
}

TSubclassOf<UGameplayEffect> AStructurePart::GetPassiveEffect() const
{
	return PassiveEffect;
}

bool AStructurePart::TryInit(AStructure* NewOwner, const bool RegisterOnly)
{
	if(OwningStructure) return false;
	
	OwningStructure = NewOwner;
	OwningStructure->RegisterPart(this, RegisterOnly, RegisterOnly);
	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	
	return true;
}

void AStructurePart::OnRegistered()
{
	if(PassiveEffect)
	{
		PassiveEffectHandle = OwningStructure->ApplyEffect(PassiveEffect);

		float Hull = 0;
		
		UGameplayEffect* Effect = PassiveEffect->GetDefaultObject<UGameplayEffect>();
		for(FGameplayModifierInfo Modifier : Effect->Modifiers)
		{
			float Magnitude;
			if(Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Magnitude))
			{
				if(Modifier.Attribute == UStructureAttributeSet::GetMaxHullAttribute()) Hull += Magnitude;
			}
		}

		OwningStructure->SetHull(OwningStructure->GetHull() + Hull);
	}
}

void AStructurePart::OnUnRegistered()
{
	if(PassiveEffectHandle.IsValid())
	{
		OwningStructure->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(PassiveEffectHandle);
		PassiveEffectHandle = FActiveGameplayEffectHandle();
	}
}

AStructure* AStructurePart::GetOwningStructure() const
{
	return OwningStructure;
}

bool AStructurePart::IsRootPart() const
{
	return IsValid(OwningStructure) && OwningStructure->GetRootPart() == this;
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

int AStructurePart::GetRootDistance() const
{
	return RootDistance;
}

void AStructurePart::ResetRootDistance()
{
	RootDistance = -1;
}

void AStructurePart::UpdateRootDistance(const int32 Distance)
{
	RootDistance = Distance;
	for(const UStructureSlot* Slot : Slots)
	{
		if(IsValid(Slot->GetAttachedSlot()) && Slot->GetAttachedSlot()->GetOwningPart()->RootDistance == -1)
		{
			Slot->GetAttachedSlot()->GetOwningPart()->UpdateRootDistance(Distance + 1);
		}
	}
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
		if(!Slot->GetAttachedSlot())
		{
			for(AStructurePart* Part : OwningStructure->GetParts())
			{
				if(Part != this)
				{
					for(UStructureSlot* Other : Part->Slots)
					{
						if((Other->GetComponentLocation() - Slot->GetComponentLocation()).IsNearlyZero(1))
						{
							Slot->TryAttach(Other);
						}
					}
				}
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
	OwningStructure->UpdateLayoutInformation();
}

void AStructurePart::ApplyDamage(const FStructureDamage Damage, const FVector HitLocation)
{
	OwningStructure->ApplyDamage(Damage, this, HitLocation);
}

UStructurePartControl* AStructurePart::CreateControl(UWidget* WidgetOwner)
{
	return nullptr;
}

TArray<const UStructureSlot*> AStructurePart::GetSlots_CDO(TSubclassOf<AStructurePart> PartClass)
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(PartClass);
	if(BPClass == nullptr) return TArray<const UStructureSlot*>();

	TArray<const UStructureSlot*> Slots;
	TArray<USCS_Node*> Nodes = BPClass->SimpleConstructionScript->GetAllNodes();
	for (const USCS_Node* Node : Nodes)
	{
		if (Node->ComponentClass == UStructureSlot::StaticClass())
		{
			Slots.Add(Cast<UStructureSlot>(Node->ComponentTemplate));
		}
	}
	return Slots;
}

TArray<const UStructureSlot*> AStructurePart::GetCompatibleSlots_CDO(const TSubclassOf<AStructurePart> PartClass, const UStructureSlot* Other)
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

const UStructureSlot* AStructurePart::GetSlot_CDO(const TSubclassOf<AStructurePart> PartClass, const FText& InName)
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
