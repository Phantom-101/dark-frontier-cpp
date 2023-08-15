// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureSectionSlotType.h"

UStructureSectionSlotType::UStructureSectionSlotType()
{
}

bool UStructureSectionSlotType::CanAttach_Implementation(UStructureSectionSlotType* Other)
{
	return GetClass() == Other->GetClass();
}
