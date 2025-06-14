// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/ItemStackEntry.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStackObject.h"

void UItemStackEntry::Init(UItemStackObject* InItemStack)
{
	if(!ensureMsgf(ItemStack == nullptr, TEXT("Init should only be called on freshly created ItemStackEntry objects")))
	{
		ItemStack->Inventory->OnChanged.RemoveAll(this);
	}
	
	ItemStack = InItemStack;
	IconImage->SetBrushFromTexture(ItemStack->Item->Icon);
	NameText->SetText(ItemStack->Item->Name);
	Update();
	ItemStack->Inventory->OnChanged.AddUObject<UItemStackEntry>(this, &UItemStackEntry::Update);
}

void UItemStackEntry::Update() const
{
	QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemStack->Inventory->GetQuantity(ItemStack->Item))));
}
