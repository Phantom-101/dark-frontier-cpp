// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDock.h"
#include "Structures/Structure.h"
#include "Structures/StructureLocation.h"

bool UStructureDock::ConfirmDock(AStructure* Structure)
{
	if(Structure == nullptr || Docker != nullptr || Structure->GetLocation()->GetDock() != nullptr)
	{
		return false;
	}
	
	Docker = Structure;
	return true;
}

bool UStructureDock::ConfirmUnDock(AStructure* Structure)
{
	if(Structure == nullptr || Docker != Structure || Structure->GetLocation()->GetDock() != this)
	{
		return false;
	}

	Docker = nullptr;
	return true;
}
