// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogItemInfo.h"
#include "CommonTextBlock.h"
#include "Items/Item.h"
#include "UI/Widgets/Visuals/InfoField.h"

void ULogItemInfo::Init(const UItem* Item) const
{
	NameText->SetText(Item->Name);
	DescriptionText->SetText(Item->Description);
	VolumeField->SetContentFromFloat(Item->Volume);
	MassField->SetContentFromFloat(Item->Mass);
	ValueField->SetContentFromFloat(Item->Value);
}
