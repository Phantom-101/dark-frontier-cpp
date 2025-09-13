// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryTradeModal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Factions/Faction.h"
#include "Items/Item.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/Inventory/QuantityInput.h"

void UInventoryTradeModal::NativeConstruct()
{
	Super::NativeConstruct();

	ListView->OnItemSelectionChanged().AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleTargetChange);
	ConfirmButton->OnClicked().AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleConfirm);
	CancelButton->OnClicked().AddUObject<UInventoryTradeModal>(this, &UInventoryTradeModal::HandleCancel);
}

void UInventoryTradeModal::Init(UStructureInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets)
{
	Inventory = InInventory;
	Item = InItem;

	ListView->SetListItems(InTargets);

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
		const float Afford = Inventory->GetStructure()->GetAffiliation()->GetFaction()->GetBalance() / Item->Value;

		const int OtherAvailable = Other->GetQuantity(Item);
		const float OtherVolumeFit = Other->GetFreeVolume() / Item->Volume;
		const float OtherMassFit = Other->GetFreeMass() / Item->Mass;
		const float OtherAfford = Other->GetStructure()->GetAffiliation()->GetFaction()->GetBalance() / Item->Value;

		const int CanBuy = FMath::Min(FMath::Min(OtherAvailable, FMath::FloorToInt(FMath::Min(VolumeFit, MassFit))), Afford);
		const int CanSell = FMath::Min(FMath::Min(Available, FMath::FloorToInt(FMath::Min(OtherVolumeFit, OtherMassFit))), OtherAfford);
		
		QuantityInput->SetBounds(CanSell, CanBuy);
	}
	else
	{
		QuantityInput->SetBounds(0, 0);
	}
	ConfirmButton->SetIsEnabled(ListView->GetSelectedItem() != nullptr);
}

void UInventoryTradeModal::HandleQuantityChange(const int Quantity) const
{
	DeltaText->SetText(FText::FromString(FString::Printf(TEXT("%d C"), FMath::RoundToInt(-Quantity * Item->Value))));
}

void UInventoryTradeModal::HandleConfirm()
{
	if(const AStructure* Target = ListView->GetSelectedItem<AStructure>())
	{
		const int Quantity = QuantityInput->GetQuantity();
		UStructureInventory* Other = Target->GetInventory();
		if(Quantity > 0)
		{
			Inventory->AddQuantity(Item, Quantity);
			Other->RemoveQuantity(Item, Quantity);
		}
		else
		{
			Inventory->RemoveQuantity(Item, Quantity);
			Other->AddQuantity(Item, Quantity);
		}
		Inventory->GetStructure()->GetAffiliation()->GetFaction()->ChangeBalance(-Quantity * Item->Value);
		Target->GetAffiliation()->GetFaction()->ChangeBalance(Quantity * Item->Value);
		DeactivateWidget();
	}
}

void UInventoryTradeModal::HandleCancel()
{
	DeactivateWidget();
}
