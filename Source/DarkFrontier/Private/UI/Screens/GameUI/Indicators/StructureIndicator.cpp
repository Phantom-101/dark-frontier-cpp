// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicator.h"

TSubclassOf<UStructureIndicatorGroup> UStructureIndicator::GetGroupClass() const
{
	return GroupClass;
}

bool UStructureIndicator::TryInit(UStructureIndication* InIndication)
{
	if(Indication != nullptr)
	{
		return false;
	}

	Indication = InIndication;
	return true;
}

UStructureIndication* UStructureIndicator::GetIndication() const
{
	return Indication;
}
