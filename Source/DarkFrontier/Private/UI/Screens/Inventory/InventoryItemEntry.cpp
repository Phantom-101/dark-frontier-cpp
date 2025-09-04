// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryItemEntry.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "UI/Screens/Inventory/InventoryItem.h"

void UInventoryItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	InventoryItem = Cast<UInventoryItem>(ListItemObject);
	InventoryItem->Inventory->OnChanged.AddUObject<UInventoryItemEntry>(this, &UInventoryItemEntry::UpdateQuantity);

	IconImage->SetBrushFromTexture(InventoryItem->Item->Icon);
	NameText->SetText(InventoryItem->Item->Name);
	UpdateQuantity();
}

void UInventoryItemEntry::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();

	InventoryItem->Inventory->OnChanged.RemoveAll(this);
	InventoryItem = nullptr;
}

void UInventoryItemEntry::UpdateQuantity() const
{
	QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), InventoryItem->Inventory->GetQuantity(InventoryItem->Item))));
}
