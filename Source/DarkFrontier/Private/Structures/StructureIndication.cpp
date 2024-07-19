// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureIndication.h"

TSubclassOf<UStructureIndicatorGroup> UStructureIndication::GetIndicatorGroupClass() const
{
	return IndicatorGroupClass;
}

TSubclassOf<UStructureIndicator> UStructureIndication::GetIndicatorClass() const
{
	return IndicatorClass;
}

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
