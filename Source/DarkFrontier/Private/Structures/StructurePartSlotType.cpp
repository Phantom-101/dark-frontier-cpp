// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlotType.h"

UStructurePartSlotType::UStructurePartSlotType()
{
}

bool UStructurePartSlotType::CanAttach_Implementation(UStructurePartSlotType* Other)
{
	return GetClass() == Other->GetClass();
}
