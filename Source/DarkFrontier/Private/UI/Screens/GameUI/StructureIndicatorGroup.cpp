// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureIndicatorGroup.h"

#include "Components/PanelWidget.h"
#include "Structures/StructureIndication.h"
#include "UI/Screens/GameUI/StructureIndicator.h"

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

void UStructureIndicatorGroup::AddIndicator(UStructureIndication* Indication)
{
	if(GetClass() == Indication->GetIndicatorGroupClass() && GetIndicator(Indication) == nullptr)
	{
		UStructureIndicator* Indicator = CreateWidget<UStructureIndicator>(this, Indication->GetIndicatorClass());
		Indicator->TryInit(Indication);
		PanelWidget->AddChild(Indicator);
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
