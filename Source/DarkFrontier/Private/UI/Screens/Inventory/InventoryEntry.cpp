// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryEntry.h"
#include "CommonTextBlock.h"
#include "Structures/Structure.h"

void UInventoryEntry::Init(const AStructure* Structure) const
{
	NameText->SetText(FText::FromString(Structure->GetName()));
}

void UInventoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject) {
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<AStructure>(ListItemObject));
}
