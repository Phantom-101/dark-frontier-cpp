// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleSectionSlotEntryObject.h"

#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"

void UCompatibleSectionSlotEntryObject::Init(const UStructureSectionSlot* SectionSlot)
{
	SectionType = SectionSlot->OwningSection->GetClass();
	SlotName = SectionSlot->SlotName;
}
