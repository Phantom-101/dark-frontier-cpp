// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryDisposeModal.h"
#include "CommonButtonBase.h"
#include "Items/Inventory.h"
#include "Items/ItemStack.h"
#include "UI/Screens/InventoryUI/QuantityInput.h"

void UInventoryDisposeModal::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UInventoryDisposeModal>(this, &UInventoryDisposeModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UInventoryDisposeModal>(this, &UInventoryDisposeModal::HandleCancel);
}

void UInventoryDisposeModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

void UInventoryDisposeModal::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	OnConfirmed.Clear();
	OnCanceled.Clear();
}

UWidget* UInventoryDisposeModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UInventoryDisposeModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UInventoryDisposeModal::Init(UInventory* InInventory, UItem* InItem)
{
	Inventory = InInventory;
	Item = InItem;
	
	QuantityInput->SetMaxQuantity(Inventory->GetItemQuantity(Item));
}

void UInventoryDisposeModal::HandleConfirm()
{
	OnConfirmed.Broadcast(FItemStack(Item, QuantityInput->GetQuantity()));
	DeactivateWidget();
	
}

void UInventoryDisposeModal::HandleCancel()
{
	OnCanceled.Broadcast();
	DeactivateWidget();
}
