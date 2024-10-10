// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicators.h"
#include "Components/CanvasPanel.h"
#include "Structures/Indications/StructureIndication.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorGroup.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorMapping.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorMappingEntry.h"

void UStructureIndicators::AddIndicator(UStructureIndication* Indication)
{
	const FStructureIndicatorMappingEntry Entry = Mapping.GetDefaultObject()->Find(Indication);
	if(Entry.IsValid())
	{
		UStructureIndicatorGroup* Group = GetGroup(Entry.GroupClass);
		if(Group != nullptr)
		{
			Group->AddIndicator(Indication, Entry.IndicatorClass);
		}
	}
}

void UStructureIndicators::RemoveIndicator(UStructureIndication* Indication)
{
	const FStructureIndicatorMappingEntry Entry = Mapping.GetDefaultObject()->Find(Indication);
	if(Entry.IsValid())
	{
		UStructureIndicatorGroup* Group = GetGroup(Entry.GroupClass);
		if(Group != nullptr)
		{
			Group->RemoveIndicator(Indication);
		}
	}
}

UStructureIndicatorGroup* UStructureIndicators::GetGroup(TSubclassOf<UStructureIndicatorGroup> GroupClass)
{
	for(UWidget* Widget : IndicatorCanvas->GetAllChildren())
	{
		if(Widget->GetClass() == GroupClass)
		{
			return Cast<UStructureIndicatorGroup>(Widget);
		}
	}
	
	return nullptr;
}
