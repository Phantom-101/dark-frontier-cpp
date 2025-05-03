// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureInventory.h"
#include "Structures/Structure.h"

UStructureInventory* UStructureInventory::CreateInventory(AStructure* Structure)
{
	UStructureInventory* Inventory = Structure->CreateDefaultSubobject<UStructureInventory>("Inventory");
	return Inventory;
}

AStructure* UStructureInventory::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}
