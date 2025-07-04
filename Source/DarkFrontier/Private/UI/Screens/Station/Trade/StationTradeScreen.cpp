﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Trade/StationTradeScreen.h"
#include "CommonButtonBase.h"
#include "Items/ItemObject.h"
#include "Structures/StructureController.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/Station/Trade/TradeEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UStationTradeScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UStationTradeScreen>(this, &UStationTradeScreen::HandleClose);
}

void UStationTradeScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();

	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	
	AStructure* Ship = Cast<AStructure>(Controller->GetPawn());
	AStructure* Station = Ship->GetLocation()->GetDockStructure();

	const UStructureInventory* ShipInventory = Ship->GetInventory();
	const UStructureInventory* StationInventory = Station->GetInventory();

	TSet Combined(ShipInventory->GetItems());
	Combined.Append(StationInventory->GetItems());
	TArray<UObject*> Items;
	for(UItem* Item : Combined)
	{
		UItemObject* Obj = NewObject<UItemObject>();
		Obj->Item = Item;
		Items.Add(Obj);
	}
	ItemListBox->SetOptions(Items);
	ItemListBox->SetBuilder([Owner = this, Class = TradeEntryClass, Ship = Ship, Station = Station](UObject* Item)
	{
		UTradeEntry* Option = CreateWidget<UTradeEntry>(Owner, Class);
		Option->Init(Cast<UItemObject>(Item)->Item, Ship->GetInventory(), Station->GetInventory());
		return Option;
	});
	
	ShipCargoBar->SetFill(FVector2D(FMath::Max(ShipInventory->GetTotalVolume01(), ShipInventory->GetTotalMass01()), 1));
	StationCargoBar->SetFill(FVector2D(FMath::Max(StationInventory->GetTotalVolume01(), StationInventory->GetTotalMass01()), 1));
}

UWidget* UStationTradeScreen::NativeGetDesiredFocusTarget() const
{
	return CloseButton;
}

void UStationTradeScreen::HandleClose()
{
	DeactivateWidget();
}
