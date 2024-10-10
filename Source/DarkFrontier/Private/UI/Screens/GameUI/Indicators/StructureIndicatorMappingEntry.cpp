// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicatorMappingEntry.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicator.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorGroup.h"

bool FStructureIndicatorMappingEntry::IsValid() const
{
	return GroupClass != nullptr && IndicatorClass != nullptr;
}
