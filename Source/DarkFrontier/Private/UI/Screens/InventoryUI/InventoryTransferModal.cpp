// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryTransferModal.h"
#include "CommonButtonBase.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/InventoryUI/InventoryEntry.h"
#include "UI/Screens/InventoryUI/QuantityInput.h"
#include "UI/Widgets/Interaction/ListBox.h"

void UInventoryTransferModal::NativeConstruct()
{
	Super::NativeConstruct();

	TargetListBox->OnChanged.Clear();
	TargetListBox->OnChanged.AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleTargetChange);
	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UInventoryTransferModal>(this, &UInventoryTransferModal::HandleCancel);
}

void UInventoryTransferModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

void UInventoryTransferModal::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	OnConfirmed.Clear();
	OnCanceled.Clear();
}

UWidget* UInventoryTransferModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UInventoryTransferModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UInventoryTransferModal::Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets)
{
	Inventory = InInventory;
	Item = InItem;

	TargetListBox->SetOptions(TArray<UObject*>(InTargets));
	TargetListBox->SetBuilder([Owner = this, Class = InventoryEntryClass](UObject* Target)
	{
		UInventoryEntry* Option = CreateWidget<UInventoryEntry>(Owner, Class);
		Option->Init(Cast<AStructure>(Target));
		return Option;
	});
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
	ConfirmButton->SetIsEnabled(TargetListBox->IsCurrentOptionValid());
}

void UInventoryTransferModal::HandleConfirm()
{
	if(TargetListBox->IsCurrentOptionValid())
	{
		OnConfirmed.Broadcast(FItemStack(Item, QuantityInput->GetQuantity()), Cast<AStructure>(TargetListBox->GetCurrentOption()));
		DeactivateWidget();
	}
}

void UInventoryTransferModal::HandleCancel()
{
	OnCanceled.Broadcast();
	DeactivateWidget();
}
