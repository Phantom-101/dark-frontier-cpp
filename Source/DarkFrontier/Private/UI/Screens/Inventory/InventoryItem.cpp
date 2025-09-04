// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryItem.h"

UInventoryItem* UInventoryItem::New(UInventory* InInventory, UItem* InItem)
{
	UInventoryItem* InventoryItem = NewObject<UInventoryItem>();
	InventoryItem->Inventory = InInventory;
	InventoryItem->Item = InItem;
	return InventoryItem;
}
