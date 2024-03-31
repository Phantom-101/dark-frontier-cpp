// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePart.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Factions/Combatant.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructurePartSlot.h"

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

FText AStructurePart::GetTypeName() const
{
	return TypeName;
}

TSubclassOf<UGameplayEffect> AStructurePart::GetPassiveEffect() const
{
	return PassiveEffect;
}

TArray<TSubclassOf<UStructureGameplayAbility>> AStructurePart::GetAbilities() const
{
	return Abilities;
}

bool AStructurePart::TryInit(AStructure* NewOwner, const bool RegisterOnly)
{
	if(OwningStructure) return false;
	
	OwningStructure = NewOwner;
	OwningStructure->RegisterPart(this, RegisterOnly, RegisterOnly);
	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	OwningFaction = OwningStructure->GetOwningFaction();
	
	return true;
}

void AStructurePart::OnRegistered()
{
	PassiveEffectHandle = OwningStructure->ApplyEffect(PassiveEffect);

	for(TSubclassOf<UStructureGameplayAbility> Ability : Abilities)
	{
		if(Ability == nullptr)
		{
			AbilityHandles.Add(FGameplayAbilitySpecHandle());
		}
		else
		{
			AbilityHandles.Add(OwningStructure->GiveAbility(Ability));
		}
	}
}

void AStructurePart::OnUnRegistered()
{
	if(PassiveEffectHandle.IsValid())
	{
		OwningStructure->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(PassiveEffectHandle);
		PassiveEffectHandle = FActiveGameplayEffectHandle();
	}

	for(FGameplayAbilitySpecHandle AbilityHandle : AbilityHandles)
	{
		if(AbilityHandle.IsValid())
		{
			OwningStructure->GetAbilitySystemComponent()->ClearAbility(AbilityHandle);
		}
	}
	AbilityHandles.Empty();
}

AStructure* AStructurePart::GetOwningStructure() const
{
	return OwningStructure;
}

bool AStructurePart::IsRootPart() const
{
	return IsValid(OwningStructure) && OwningStructure->GetRootPart() == this;
}

bool AStructurePart::IsActiveInLayout()
{
	// Add hp to structure parts
	return true;
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

TArray<UStructurePartSlot*> AStructurePart::GetSlots()
{
	return Slots;
}

TArray<UStructurePartSlot*> AStructurePart::GetCompatibleSlots(const UStructurePartSlot* Other)
{
	TArray<UStructurePartSlot*> Ret;
	Ret.Reserve(Slots.Num());
	for(UStructurePartSlot* Slot : Slots)
	{
		if(Slot->CanAttach(Other)) Ret.Add(Slot);
	}
	return Ret;
}

UStructurePartSlot* AStructurePart::GetSlot(const FText InName)
{
	for(UStructurePartSlot* Slot : Slots)
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
	for(UStructurePartSlot* Slot : Slots)
	{
		if(!Slot->GetAttachedSlot())
		{
			for(AStructurePart* Part : OwningStructure->GetParts())
			{
				if(Part != this)
				{
					for(UStructurePartSlot* Other : Part->Slots)
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
	for(UStructurePartSlot* Slot : Slots)
	{
		Slot->TryDetach();
	}
	OwningStructure->UpdateLayoutInformation();
}

void AStructurePart::UpdateDistance(const int32 Distance)
{
	RootDistance = Distance;
	for(const UStructurePartSlot* Slot : Slots)
	{
		if(IsValid(Slot->GetAttachedSlot()) && Slot->GetAttachedSlot()->GetOwningPart()->RootDistance == -1)
		{
			Slot->GetAttachedSlot()->GetOwningPart()->UpdateDistance(Distance + 1);
		}
	}
}

float AStructurePart::GetArcLength(TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	return 1;
}

FLinearColor AStructurePart::GetArcColor(TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	return FLinearColor::White;
}

void AStructurePart::ActivateAbility(const TSubclassOf<UStructureGameplayAbility> AbilityClass)
{
	if(Abilities.Contains(AbilityClass))
	{
		OwningStructure->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandles[Abilities.IndexOfByKey(AbilityClass)]);
	}
}

void AStructurePart::TickCombatants()
{
	// Remove depleted armies
	for(int i = Combatants.Num() - 1; i >= 0; i--)
	{
		if(Combatants[i]->Count <= 0)
		{
			Combatants.RemoveAt(i);
		}
	}
	
	// Tabulate combatants on both sides
	TArray<UCombatant*> DefenderCombatants;
	TArray<UCombatant*> AttackerCombatants;

	// Calculate strengths based on attacker attack and defender defense
	double DefenderStrength = 0;
	double AttackerStrength = 0;

	for(UCombatant* Combatant : Combatants)
	{
		Combatant->BuffMultiplier = 1;
		const double Relation = Combatant->OwningFaction->GetRelation(OwningStructure->GetOwningFaction());
		if(Relation == 1)
		{
			DefenderCombatants.Add(Combatant);
			DefenderStrength += Combatant->Defense * Combatant->Count;
		}
		else if (Relation == -1)
		{
			AttackerCombatants.Add(Combatant);
			AttackerStrength += Combatant->Attack * Combatant->Count;
		}
	}

	if(DefenderCombatants.Num() == 0)
	{
		// Garrison defeated

		if(AttackerCombatants.Num() > 0)
		{
			OwningFaction = AttackerCombatants[0]->OwningFaction;

			if(this == OwningStructure->GetRootPart())
			{
				OwningStructure->SetOwningFaction(OwningFaction);
				// todo process ai changes
				// Do not send attacker combatants because they are now the defenders
			}
			else
			{
				// Send attacker combatants to the connected part that is closest to the root part
				if(Slots.Num() > 0)
				{
					AStructurePart* Target = Slots[0]->GetAttachedSlot()->GetOwningPart();
					int32 MinDistance = Target->RootDistance;
					for(int i = 1; i < Slots.Num(); i++)
					{
						AStructurePart* Part = Slots[i]->GetAttachedSlot()->GetOwningPart();
						if(Part->RootDistance < MinDistance)
						{
							Target = Part;
							MinDistance = Part->RootDistance;
						}
					}
					// Combatants are added to a list to be added after all parts have had their combat ticks
					// This is to avoid timing issues where results of ticks can change depending on whether neighboring parts have sent attacker combatants already
					for(UCombatant* Combatant : AttackerCombatants)
					{
						Target->QueuedCombatants.Add(Combatant);
						Combatants.Remove(Combatant);
					}
				}
			}
		}
	}
	else
	{
		if(AttackerCombatants.Num() != 0)
		{
			// Give 1.5x effectiveness buff to the side with the greater strength
			const bool DefenderHasAdvantage = DefenderStrength >= AttackerStrength;

			constexpr double BuffValue = 1.5;
			const double DefenderBuff = DefenderHasAdvantage ? BuffValue : 1;
			const double AttackerBuff = !DefenderHasAdvantage ? BuffValue : 1;

			// Pre set defender army buffs so subsequent damage calculations are correct
			for(UCombatant* Combatant : DefenderCombatants)
			{
				Combatant->BuffMultiplier = DefenderBuff;
			}

			// Each attacker army deals attack and takes counterattack
			for(UCombatant* Combatant : AttackerCombatants)
			{
				Combatant->BuffMultiplier = AttackerBuff;
				Combatant->AttackTarget(Combatant->GetPreferredTarget(DefenderCombatants));
			}

			// Defender armies attack second
			for(UCombatant* Combatant : DefenderCombatants)
			{
				if(Combatant->Count > 0)
				{
					Combatant->AttackTarget(Combatant->GetPreferredTarget(AttackerCombatants));
				}
			}
		}
	}
}

void AStructurePart::DequeueCombatants()
{
	for(UCombatant* Combatant : QueuedCombatants)
	{
		Combatants.Add(Combatant);
	}
	QueuedCombatants.Empty();
}

TArray<const UStructurePartSlot*> AStructurePart::GetSlots_CDO(TSubclassOf<AStructurePart> PartClass)
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(PartClass);
	if(!BPClass) return TArray<const UStructurePartSlot*>();

	TArray<const UStructurePartSlot*> Slots;
	TArray<USCS_Node*> Nodes = BPClass->SimpleConstructionScript->GetAllNodes();
	for (const USCS_Node* Node : Nodes)
	{
		if (Node->ComponentClass == UStructurePartSlot::StaticClass())
		{
			Slots.Add(Cast<UStructurePartSlot>(Node->ComponentTemplate));
		}
	}
	return Slots;
}

TArray<const UStructurePartSlot*> AStructurePart::GetCompatibleSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructurePartSlot* Other)
{
	TArray<const UStructurePartSlot*> CDOSlots = GetSlots_CDO(PartClass);
	TArray<const UStructurePartSlot*> Ret;
	Ret.Reserve(CDOSlots.Num());
	for(const UStructurePartSlot* Slot : CDOSlots)
	{
		if(Slot->CanAttach(Other)) Ret.Add(Slot);
	}
	return Ret;
}

const UStructurePartSlot* AStructurePart::GetSlot_CDO(TSubclassOf<AStructurePart> PartClass, FText InName)
{
	for(const UStructurePartSlot* Slot : GetSlots_CDO(PartClass))
	{
		if(Slot->GetSlotName().EqualTo(InName))
		{
			return Slot;
		}
	}
	
	return nullptr;
}
