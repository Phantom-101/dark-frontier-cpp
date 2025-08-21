// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryTransferModal.h"
#include "CommonButtonBase.h"
#include "Components/ListView.h"
#include "Items/Item.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/Inventory/QuantityInput.h"

void UInventoryTransferModal::NativeConstruct()
{
	Super::NativeConstruct();

	ListView->OnItemSelectionChanged().AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleTargetChange);
	ConfirmButton->OnClicked().AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleConfirm);
	CancelButton->OnClicked().AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleCancel);
}

void UInventoryTransferModal::Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets)
{
	Inventory = InInventory;
	Item = InItem;

	ListView->SetListItems(InTargets);
}

void UInventoryTransferModal::HandleTargetChange(UObject* Target) const
{
	if(IsValid(Target))
	{
		const UStructureInventory* TargetInventory = Cast<AStructure>(Target)->GetInventory();
		const int Available = Inventory->GetQuantity(Item);
		const float VolumeFit = TargetInventory->GetFreeVolume() / Item->Volume;
		const float MassFit = TargetInventory->GetFreeMass() / Item->Mass;
		QuantityInput->SetMaxQuantity(FMath::Min(Available, FMath::FloorToInt(FMath::Min(VolumeFit, MassFit))));
	}
	else
	{
		QuantityInput->SetMaxQuantity(0);
	}
	ConfirmButton->SetIsEnabled(ListView->GetSelectedItem() != nullptr);
}

void UInventoryTransferModal::HandleConfirm()
{
	if(const AStructure* Target = ListView->GetSelectedItem<AStructure>())
	{
		Inventory->RemoveQuantity(Item, QuantityInput->GetQuantity());
		Target->GetInventory()->AddQuantity(Item, QuantityInput->GetQuantity());
		DeactivateWidget();
	}
}

void UInventoryTransferModal::HandleCancel()
{
	DeactivateWidget();
}
