// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicators.h"
#include "Components/CanvasPanel.h"
#include "Structures/Indications/StructureIndication.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicator.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorGroup.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorMapping.h"

void UStructureIndicators::AddIndicator(UStructureIndication* Indication) const
{
	const TSubclassOf<UStructureIndicator> IndicatorClass = Mapping->Map(Indication->GetClass());
	if(IndicatorClass != nullptr)
	{
		UStructureIndicatorGroup* Group = GetGroup(IndicatorClass.GetDefaultObject()->GetGroupClass());
		if(Group != nullptr)
		{
			Group->AddIndicator(Indication, IndicatorClass);
		}
	}
}

void UStructureIndicators::RemoveIndicator(UStructureIndication* Indication) const
{
	const TSubclassOf<UStructureIndicator> IndicatorClass = Mapping->Map(Indication->GetClass());
	if(IndicatorClass != nullptr)
	{
		UStructureIndicatorGroup* Group = GetGroup(IndicatorClass.GetDefaultObject()->GetGroupClass());
		if(Group != nullptr)
		{
			Group->RemoveIndicator(Indication);
		}
	}
}

UStructureIndicatorGroup* UStructureIndicators::GetGroup(const TSubclassOf<UStructureIndicatorGroup> GroupClass) const
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
