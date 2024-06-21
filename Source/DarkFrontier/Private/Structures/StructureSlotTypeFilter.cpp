// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureSlotTypeFilter.h"
#include "Structures/StructureSlot.h"

bool UStructureSlotTypeFilter::IsCompatible(const UStructureSlot* Other)
{
	return CompatibleTypes.Contains(Other->GetSlotType());
}
