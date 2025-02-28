// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/ItemStackEntry.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStackObject.h"

void UItemStackEntry::Init(UItemStackObject* InItemStack)
{
	if(!ensureMsgf(ItemStack == nullptr, TEXT("Init called on ItemStackEntry with non-null item stack")))
	{
		ItemStack->Inventory->OnItemChanged.RemoveAll(this);
	}
	
	ItemStack = InItemStack;
	IconImage->SetBrushFromTexture(ItemStack->Item->Icon);
	NameText->SetText(ItemStack->Item->Name);
	UpdateQuantity(ItemStack->Item, ItemStack->Inventory->GetItemQuantity(ItemStack->Item));
	ItemStack->Inventory->OnItemChanged.AddUObject<UItemStackEntry>(this, &UItemStackEntry::UpdateQuantity);
}

void UItemStackEntry::UpdateQuantity(UItem* InItem, const int InQuantity) const
{
	if(ItemStack->Item == InItem)
	{
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), InQuantity)));
	}
}
