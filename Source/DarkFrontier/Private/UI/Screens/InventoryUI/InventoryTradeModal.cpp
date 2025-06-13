// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryTradeModal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Factions/Faction.h"
#include "Items/Item.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
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

UWidget* UInventoryTradeModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UInventoryTradeModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UInventoryTradeModal::Init(UStructureInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets)
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
		const UStructureInventory* Other = Cast<AStructure>(Target)->GetInventory();
		
		const int Available = Inventory->GetQuantity(Item);
		const float VolumeFit = Inventory->GetFreeVolume() / Item->Volume;
		const float MassFit = Inventory->GetFreeMass() / Item->Mass;
		const float Afford = Inventory->GetStructure()->GetOwningFaction()->GetBalance() / Item->Value;

		const int OtherAvailable = Other->GetQuantity(Item);
		const float OtherVolumeFit = Other->GetFreeVolume() / Item->Volume;
		const float OtherMassFit = Other->GetFreeMass() / Item->Mass;
		const float OtherAfford = Other->GetStructure()->GetOwningFaction()->GetBalance() / Item->Value;

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
		const int Quantity = QuantityInput->GetQuantity();
		UStructureInventory* Target = Cast<AStructure>(TargetListBox->GetCurrentOption())->GetInventory();
		if(Quantity > 0)
		{
			Inventory->AddQuantity(Item, Quantity);
			Target->RemoveQuantity(Item, Quantity);
		}
		else
		{
			Inventory->RemoveQuantity(Item, Quantity);
			Target->AddQuantity(Item, Quantity);
		}
		Inventory->GetStructure()->GetOwningFaction()->ChangeBalance(-Quantity * Item->Value);
		Target->GetStructure()->GetOwningFaction()->ChangeBalance(Quantity * Item->Value);
		DeactivateWidget();
	}
}

void UInventoryTradeModal::HandleCancel()
{
	DeactivateWidget();
}
