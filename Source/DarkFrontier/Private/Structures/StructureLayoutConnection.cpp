// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayoutConnection.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

FStructureLayoutConnection::FStructureLayoutConnection()
{
}

FStructureLayoutConnection::FStructureLayoutConnection(const UStructurePartSlot* SlotA, const UStructurePartSlot* SlotB)
{
	PartAId = SlotA->GetOwningPart()->GetPartId();
	PartASlot = SlotA->GetSlotName();
	PartBId = SlotB->GetOwningPart()->GetPartId();
	PartBSlot = SlotB->GetSlotName();
}

bool FStructureLayoutConnection::IsValid() const
{
	return PartAId >= 0 && PartBId >= 0;
}
