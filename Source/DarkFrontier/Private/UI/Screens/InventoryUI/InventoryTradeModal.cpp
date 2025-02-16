// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryTradeModal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Factions/Faction.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Structures/Structure.h"
#include "UI/Screens/InventoryUI/InventoryEntry.h"
#include "UI/Screens/InventoryUI/QuantityInput.h"
#include "UI/Widgets/Interaction/ListBox.h"

void UInventoryTradeModal::NativeConstruct()
{
	Super::NativeConstruct();

	TargetListBox->OnChanged.Clear();
	TargetListBox->OnChanged.AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleTargetChange);
	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleCancel);
}

void UInventoryTradeModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

void UInventoryTradeModal::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	OnConfirmed.Clear();
	OnCanceled.Clear();
}

UWidget* UInventoryTradeModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UInventoryTradeModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UInventoryTradeModal::Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets)
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

	HandleQuantityChange(QuantityInput->GetQuantity());
}

void UInventoryTradeModal::HandleTargetChange(UObject* Target) const
{
	if(IsValid(Target))
	{
		UInventory* TargetInventory = Cast<AStructure>(Target)->GetInventory();
		
		const int Available = Inventory->GetItemQuantity(Item);
		const float VolumeFit = Inventory->GetVolumeRemaining() / Item->Volume;
		const float MassFit = Inventory->GetMassRemaining() / Item->Mass;
		const float Afford = Inventory->GetStructure()->GetOwningFaction()->GetBalance() / Item->Value;

		const int OtherAvailable = TargetInventory->GetItemQuantity(Item);
		const float OtherVolumeFit = TargetInventory->GetVolumeRemaining() / Item->Volume;
		const float OtherMassFit = TargetInventory->GetMassRemaining() / Item->Mass;
		const float OtherAfford = TargetInventory->GetStructure()->GetOwningFaction()->GetBalance() / Item->Value;

		const int CanBuy = FMath::Min(FMath::Min(OtherAvailable, FMath::FloorToInt(FMath::Min(VolumeFit, MassFit))), Afford);
		const int CanSell = FMath::Min(FMath::Min(Available, FMath::FloorToInt(FMath::Min(OtherVolumeFit, OtherMassFit))), OtherAfford);
		
		QuantityInput->SetBounds(CanSell, CanBuy);
	}
	else
	{
		QuantityInput->SetBounds(0, 0);
	}
	ConfirmButton->SetIsEnabled(TargetListBox->IsCurrentOptionValid());
}

void UInventoryTradeModal::HandleQuantityChange(const int Quantity) const
{
	DeltaText->SetText(FText::FromString(FString::Printf(TEXT("%d C"), FMath::RoundToInt(-Quantity * Item->Value))));
}

void UInventoryTradeModal::HandleConfirm()
{
	if(TargetListBox->IsCurrentOptionValid())
	{
		OnConfirmed.Broadcast(FItemStack(Item, QuantityInput->GetQuantity()), Cast<AStructure>(TargetListBox->GetCurrentOption()));
		DeactivateWidget();
	}
}

void UInventoryTradeModal::HandleCancel()
{
	OnCanceled.Broadcast();
	DeactivateWidget();
}
