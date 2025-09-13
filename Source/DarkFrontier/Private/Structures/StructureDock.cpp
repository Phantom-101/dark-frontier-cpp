// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDock.h"
#include "Structures/Structure.h"

AStructure* UStructureDock::GetDocker() const
{
	return Docker;
}

bool UStructureDock::ConfirmDock(AStructure* Structure)
{
	if(Structure == nullptr || Docker != nullptr || Structure->GetDockable()->GetDock() != nullptr)
	{
		return false;
	}
	
	Docker = Structure;
	return true;
}

bool UStructureDock::ConfirmUnDock(AStructure* Structure)
{
	if(Structure == nullptr || Docker != Structure || Structure->GetDockable()->GetDock() != this)
	{
		return false;
	}

	Docker = nullptr;
	return true;
}
