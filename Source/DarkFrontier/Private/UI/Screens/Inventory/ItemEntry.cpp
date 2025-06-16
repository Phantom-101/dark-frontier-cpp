// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/ItemEntry.h"
#include "CommonTextBlock.h"
#include "Items/Item.h"
#include "Items/ItemObject.h"

void UItemEntry::Init(const UItemObject* ItemObject) const
{
	NameText->SetText(ItemObject->Item->Name);
}
