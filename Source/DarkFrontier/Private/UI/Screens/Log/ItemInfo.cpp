// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/ItemInfo.h"
#include "CommonTextBlock.h"
#include "Items/Item.h"
#include "Items/ItemObject.h"
#include "UI/Screens/Inventory/ItemEntry.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UItemInfo::Init(const UItemObject* ItemObject) const
{
	Header->Init(ItemObject);
	DescriptionText->SetText(ItemObject->Item->Description);
	VolumeField->SetContentFromFloat(ItemObject->Item->Volume);
	MassField->SetContentFromFloat(ItemObject->Item->Mass);
	ValueField->SetContentFromFloat(ItemObject->Item->Value);
}
