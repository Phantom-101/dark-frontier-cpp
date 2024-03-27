// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlotTypeFilter.h"
#include "Structures/StructurePartSlot.h"

bool UStructurePartSlotTypeFilter::IsCompatible(const UStructurePartSlot* Other)
{
	return CompatibleTypes.Contains(Other->GetSlotType());
}
