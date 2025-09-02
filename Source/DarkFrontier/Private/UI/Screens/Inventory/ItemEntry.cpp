// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/ItemEntry.h"
#include "CommonTextBlock.h"
#include "Items/Item.h"

void UItemEntry::Init(const UItem* Item) const
{
	NameText->SetText(Item->Name);
}

void UItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UItem>(ListItemObject));
}
