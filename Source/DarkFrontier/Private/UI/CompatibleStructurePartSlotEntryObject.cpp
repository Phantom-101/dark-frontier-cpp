// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartSlotEntryObject.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

void UCompatibleStructurePartSlotEntryObject::Init(const UStructurePartSlot* PartSlot)
{
	PartClass = PartSlot->GetOwningPart()->GetClass();
	SlotName = PartSlot->GetSlotName();
}
