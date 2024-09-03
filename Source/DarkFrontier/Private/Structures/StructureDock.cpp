// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDock.h"
#include "Structures/Structure.h"

bool UStructureDock::ConfirmDock(AStructure* Structure)
{
	if(!IsValid(Structure))
	{
		return false;
	}

	if(Docker != nullptr)
	{
		return false;
	}

	if(Structure->GetDock() != nullptr)
	{
		return false;
	}
	
	Docker = Structure;
	return true;
}

bool UStructureDock::ConfirmUnDock(AStructure* Structure)
{
	if(!IsValid(Structure))
	{
		return false;
	}

	if(Docker != Structure)
	{
		return false;
	}

	if(Structure->GetDock() != this)
	{
		return false;
	}

	Docker = nullptr;
	return true;
}
