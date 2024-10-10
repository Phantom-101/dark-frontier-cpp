// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicatorMapping.h"
#include "Log.h"
#include "Structures/Indications/StructureIndication.h"

FStructureIndicatorMappingEntry UStructureIndicatorMapping::Find(const TSubclassOf<UStructureIndication>& IndicationClass)
{
	if(IndicationClass == nullptr)
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Attempted mapping of null indication class"))
		return DefaultEntry;
	}
	
	if(Entries.Contains(IndicationClass))
	{
		return Entries[IndicationClass];
	}

	return DefaultEntry;
}

FStructureIndicatorMappingEntry UStructureIndicatorMapping::Find(const UStructureIndication* Indication)
{
	return Find(Indication->GetClass());
}
