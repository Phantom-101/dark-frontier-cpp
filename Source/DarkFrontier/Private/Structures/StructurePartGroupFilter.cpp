// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartGroupFilter.h"
#include "Structures/StructurePart.h"

bool UStructurePartGroupFilter::IsCompatible(const AStructurePart* Other)
{
	return CompatibleGroups.Contains(Other->GetPartType());
}
