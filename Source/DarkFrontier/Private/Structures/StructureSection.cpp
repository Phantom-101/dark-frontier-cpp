// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureSection.h"
#include "Structures/Structure.h"
#include "Structures/StructureEquipmentSlot.h"
#include "Structures/StructureSectionSlot.h"
#include "Structures/StructureSectionSlotType.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

AStructureSection::AStructureSection()
{
}

void AStructureSection::BeginPlay()
{
	Super::BeginPlay();
}

void AStructureSection::InitOwningStructure(AStructure* NewOwner)
{
	OwningStructure = NewOwner;
	OwningStructure->RegisterSection(this);
	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
}

void AStructureSection::RegisterSectionSlot(UStructureSectionSlot* Slot)
{
	SectionSlots.Add(Slot);
}

UStructureSectionSlot* AStructureSection::GetSectionSlotByName(const FText Name)
{
	for(UStructureSectionSlot* Slot : SectionSlots)
	{
		if(Slot->SlotName.EqualToCaseIgnored(Name))
		{
			return Slot;
		}
	}
	
	return nullptr;
}

TArray<UStructureSectionSlot*> AStructureSection::GetCompatibleSectionSlots(TSubclassOf<UStructureSectionSlotType> SlotType)
{
	TArray<UStructureSectionSlot*> Ret;
	for(UStructureSectionSlot* Slot : SectionSlots)
	{
		if(Slot->SlotType.GetDefaultObject()->CanAttach(SlotType.GetDefaultObject()))
		{
			Ret.Add(Slot);
		}
	}
	return Ret;
}

void AStructureSection::AttachNearbySectionSlots()
{
	for(UStructureSectionSlot* Slot : SectionSlots)
	{
		if(Slot->AttachedSlot == nullptr)
		{
			for(AStructureSection* Section : OwningStructure->GetCachedSections())
			{
				if(Section != this)
				{
					for(UStructureSectionSlot* Candidate : Section->SectionSlots)
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

void AStructureSection::RegisterEquipmentSlot(UStructureEquipmentSlot* Slot)
{
	EquipmentSlots.Add(Slot);
}

UStructureEquipmentSlot* AStructureSection::GetEquipmentSlotByName(const FText Name)
{
	for(UStructureEquipmentSlot* Slot : EquipmentSlots)
	{
		if(Slot->SlotName.EqualToCaseIgnored(Name))
		{
			return Slot;
		}
	}
	
	return nullptr;
}

void AStructureSection::RemoveSection()
{
	if(OwningStructure->GetRootSection() != this)
	{
		for(UStructureSectionSlot* Slot : SectionSlots)
		{
			Slot->Detach();
		}
		OwningStructure->UpdateSections();
	}
}
