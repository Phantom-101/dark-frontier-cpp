// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicators.h"
#include "Components/CanvasPanel.h"
#include "Structures/Indications/StructureIndication.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicatorGroup.h"

void UStructureIndicators::AddIndicator(UStructureIndication* Indication)
{
	UStructureIndicatorGroup* Group = GetIndicatorGroup(Indication);

	if(Group != nullptr)
	{
		Group->AddIndicator(Indication);
	}
}

void UStructureIndicators::RemoveIndicator(UStructureIndication* Indication)
{
	UStructureIndicatorGroup* Group = GetIndicatorGroup(Indication);

	if(Group != nullptr)
	{
		Group->RemoveIndicator(Indication);
	}
}

UStructureIndicatorGroup* UStructureIndicators::GetIndicatorGroup(UStructureIndication* Indication)
{
	for(UWidget* Widget : IndicatorCanvas->GetAllChildren())
	{
		if(Widget->GetClass() == Indication->IndicatorGroupClass)
		{
			return Cast<UStructureIndicatorGroup>(Widget);
		}
	}
	
	return nullptr;
}
