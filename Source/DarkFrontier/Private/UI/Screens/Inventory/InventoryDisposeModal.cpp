// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryDisposeModal.h"
#include "CommonButtonBase.h"
#include "Items/Inventory.h"
#include "UI/Screens/Inventory/QuantityInput.h"

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
	
	QuantityInput->SetMaxQuantity(Inventory->GetQuantity(Item));
}

void UInventoryDisposeModal::HandleConfirm()
{
	Inventory->RemoveQuantity(Item, QuantityInput->GetQuantity());
	DeactivateWidget();
}

void UInventoryDisposeModal::HandleCancel()
{
	DeactivateWidget();
}
