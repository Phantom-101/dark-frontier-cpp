// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Controls/StructurePartControls.h"
#include "Structures/StructurePart.h"

bool UStructurePartControls::TryInitialize(AStructurePart* InPart)
{
	if(Part == nullptr && IsValid(InPart))
	{
		Part = InPart;
		return true;
	}

	return false;
}

AStructurePart* UStructurePartControls::GetPart()
{
	return Part;
}
