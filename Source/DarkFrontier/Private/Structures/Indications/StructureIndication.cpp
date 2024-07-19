// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/StructureIndication.h"

bool UStructureIndication::TryInit(AStructure* InStructure)
{
	if(Structure != nullptr)
	{
		return false;
	}

	Structure = InStructure;
	return true;
}

AStructure* UStructureIndication::GetStructure() const
{
	return Structure;
}
