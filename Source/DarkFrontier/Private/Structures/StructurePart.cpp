// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePart.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Factions/Army.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "Structures/StructurePartAction.h"
#include "Structures/StructurePartActionGroup.h"
#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePartSlotType.h"

AStructurePart::AStructurePart()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStructurePart::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UStructurePartSlot>(Slots);
}

void AStructurePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// stuff here
}

void AStructurePart::InitOwningStructure(AStructure* NewOwner)
{
	OwningStructure = NewOwner;
	OwningStructure->RegisterPart(this);
	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	ControlledBy = OwningStructure->OwningFaction;
}

void AStructurePart::OnRegistered()
{
	OwningStructure->ApplyEffect(AttributeEffect);
	if(ActionGroupType && ActionType)
	{
		Action = OwningStructure->RegisterAction(ActionGroupType, ActionType);
	}
}

void AStructurePart::OnUnregistered()
{
	FGameplayEffectQuery Query;
	Query.EffectDefinition = AttributeEffect;
	TArray<FActiveGameplayEffectHandle> Handles = OwningStructure->GetAbilitySystemComponent()->GetActiveEffects(Query);
	if(Handles.Num() > 0)
	{
		OwningStructure->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(Handles[0]);
	}
	if(ActionGroupType && Action)
	{
		OwningStructure->UnregisterAction(ActionGroupType, Action);
	}
}

void AStructurePart::RegisterPartSlot(UStructurePartSlot* Slot)
{
	PartSlots.Add(Slot);
}

TArray<const UStructurePartSlot*> AStructurePart::GetCompatiblePartSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructurePartSlot* Other)
{
	TArray<UStructurePartSlot*> Slots;
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(PartClass);
	
	if(BPClass == nullptr)
	{
		return TArray<const UStructurePartSlot*>();
	}
	
	TArray<USCS_Node*> Nodes = BPClass->SimpleConstructionScript->GetAllNodes();
	for (const USCS_Node* Node : Nodes)
	{
		if (Node->ComponentClass == UStructurePartSlot::StaticClass())
		{
			Slots.Add(Cast<UStructurePartSlot>(Node->ComponentTemplate));
		}
	}
	
	TArray<const UStructurePartSlot*> Ret;
	for(const UStructurePartSlot* Slot : Slots)
	{
		if(Slot->CanAttach(Other))
		{
			Ret.Add(Slot);
		}
	}
	return Ret;
}

void AStructurePart::AttachNearbyPartSlots()
{
	for(UStructurePartSlot* Slot : PartSlots)
	{
		if(Slot->AttachedSlot == nullptr)
		{
			for(AStructurePart* Part : OwningStructure->GetCachedParts())
			{
				if(Part != this)
				{
					for(UStructurePartSlot* Candidate : Part->PartSlots)
					{
						if((Candidate->GetComponentLocation() - Slot->GetComponentLocation()).IsNearlyZero(1))
						{
							Slot->Attach(Candidate);
						}
					}
				}
			}
		}
	}
}

void AStructurePart::RemovePart()
{
	if(OwningStructure->GetRootPart() != this)
	{
		for(UStructurePartSlot* Slot : PartSlots)
		{
			Slot->Detach();
		}
		OwningStructure->UpdateCachedParts();
	}
}

void AStructurePart::PropagateDistanceUpdate(const int32 Distance)
{
	DistanceToRoot = Distance;
	for(const UStructurePartSlot* Slot : PartSlots)
	{
		if(Slot->AttachedSlot != nullptr && Slot->AttachedSlot->OwningPart->DistanceToRoot == -1)
		{
			Slot->AttachedSlot->OwningPart->PropagateDistanceUpdate(Distance + 1);
		}
	}	
}

void AStructurePart::TickArmies()
{
	// Remove depleted armies
	for(int i = Armies.Num() - 1; i >= 0; i--)
	{
		if(Armies[i]->Count <= 0)
		{
			Armies.RemoveAt(i);
		}
	}
	
	// Tabulate armies on both sides
	TArray<UArmy*> DefenderArmies;
	TArray<UArmy*> AttackerArmies;

	// Calculate strengths based on attacker attack and defender defense
	double DefenderStrength = 0;
	double AttackerStrength = 0;

	for(UArmy* Army : Armies)
	{
		Army->BuffMultiplier = 1;
		const double Relation = Army->OwningFaction->GetRelation(OwningStructure->OwningFaction);
		if(Relation == 1)
		{
			DefenderArmies.Add(Army);
			DefenderStrength += Army->Defense * Army->Count;
		}
		else if (Relation == -1)
		{
			AttackerArmies.Add(Army);
			AttackerStrength += Army->Attack * Army->Count;
		}
	}

	if(DefenderArmies.Num() == 0)
	{
		// Garrison defeated

		ControlledBy = AttackerArmies[0]->OwningFaction;

		if(this == OwningStructure->GetRootPart())
		{
			OwningStructure->OwningFaction = ControlledBy;
			// todo process ai changes
			// Do not send attacker armies because they are now the defenders
		}
		else
		{
			// Send attacker armies to the connected part that is closest to the root part
			if(PartSlots.Num() > 0)
			{
				AStructurePart* Target = PartSlots[0]->AttachedSlot->OwningPart;
				int32 MinDistance = Target->DistanceToRoot;
				for(int i = 1; i < PartSlots.Num(); i++)
				{
					AStructurePart* Part = PartSlots[i]->AttachedSlot->OwningPart;
					if(Part->DistanceToRoot < MinDistance)
					{
						Target = Part;
						MinDistance = Part->DistanceToRoot;
					}
				}
				// Armies are added to a list to be added after all parts have had their army ticks
				// This is to avoid timing issues where results of ticks can change depending on whether neighboring parts have sent attacker armies already
				for(UArmy* Army : AttackerArmies)
				{
					Target->ArrivingArmies.Add(Army);
					Armies.Remove(Army);
				}
			}
		}
	}
	else
	{
		if(AttackerArmies.Num() != 0)
		{
			// Give 1.5x effectiveness buff to the side with the greater strength
			const bool DefenderHasAdvantage = DefenderStrength >= AttackerStrength;

			constexpr double BuffValue = 1.5;
			const double DefenderBuff = DefenderHasAdvantage ? BuffValue : 1;
			const double AttackerBuff = !DefenderHasAdvantage ? BuffValue : 1;

			// Pre set defender army buffs so subsequent damage calculations are correct
			for(UArmy* Army : DefenderArmies)
			{
				Army->BuffMultiplier = DefenderBuff;
			}

			// Each attacker army deals attack and takes counterattack
			for(UArmy* Army : AttackerArmies)
			{
				Army->BuffMultiplier = AttackerBuff;
				Army->AttackTarget(Army->GetPreferredTarget(DefenderArmies));
			}

			// Defender armies attack second
			for(UArmy* Army : DefenderArmies)
			{
				if(Army->Count > 0)
				{
					Army->AttackTarget(Army->GetPreferredTarget(AttackerArmies));
				}
			}
		}
	}
}

void AStructurePart::ProcessArrivingArmies()
{
	for(UArmy* Army : ArrivingArmies)
	{
		Armies.Add(Army);
	}

	ArrivingArmies.Empty();
}

bool AStructurePart::IsRootPart() const
{
	return OwningStructure != nullptr && OwningStructure->GetRootPart() == this;
}

bool AStructurePart::IsActive()
{
	// Add hp to structure parts
	return true;
}

TArray<UStructurePartSlot*> AStructurePart::GetSlots()
{
	return Slots;
}

UStructurePartSlot* AStructurePart::GetSlot(const FText InName)
{
	for(UStructurePartSlot* Slot : Slots)
	{
		if(Slot->SlotName.EqualTo(InName))
		{
			return Slot;
		}
	}
	
	return nullptr;
}

TArray<UStructurePartSlot*> AStructurePart::GetCompatibleSlots(const UStructurePartSlot* Other)
{
	TArray<UStructurePartSlot*> Ret;
	for(UStructurePartSlot* Slot : Slots)
	{
		if(Slot->CanAttach(Other)) Ret.Add(Slot);
	}
	return Ret;
}
