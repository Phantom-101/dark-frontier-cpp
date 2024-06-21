// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructureSlotEntryObject.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"

void UCompatibleStructureSlotEntryObject::Init(const UStructureSlot* InSlot)
{
	PartClass = InSlot->GetOwningPart()->GetClass();
	SlotName = InSlot->GetSlotName();
}
