// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Indicators/StructureIndicatorGroup.h"
#include "Components/PanelWidget.h"
#include "UI/Screens/Flight/Indicators/StructureIndicator.h"

class UStructureIndicator;

UStructureIndicator* UStructureIndicatorGroup::GetIndicator(UStructureIndication* Indication)
{
	for(UWidget* Widget : PanelWidget->GetAllChildren())
	{
		UStructureIndicator* Indicator = Cast<UStructureIndicator>(Widget);
		if(Indicator != nullptr && Indicator->GetIndication() == Indication)
		{
			return Indicator;
		}
	}
	
	return nullptr;
}

void UStructureIndicatorGroup::AddIndicator(UStructureIndication* Indication, const TSubclassOf<UStructureIndicator>& IndicatorClass)
{
	if(IndicatorClass != nullptr && GetIndicator(Indication) == nullptr)
	{
		UStructureIndicator* Indicator = CreateWidget<UStructureIndicator>(this, IndicatorClass);
		PanelWidget->AddChild(Indicator);
		Indicator->TryInit(Indication);
	}
}

void UStructureIndicatorGroup::RemoveIndicator(UStructureIndication* Indication)
{
	UStructureIndicator* Indicator = GetIndicator(Indication);
	if(Indicator != nullptr)
	{
		PanelWidget->RemoveChild(Indicator);
	}
}
