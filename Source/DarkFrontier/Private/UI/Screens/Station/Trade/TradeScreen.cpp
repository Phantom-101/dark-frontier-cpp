// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Trade/TradeScreen.h"
#include "CommonButtonBase.h"
#include "Components/ListView.h"
#include "Structures/StructureController.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/Station/Trade/TradeEntry.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UTradeScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UTradeScreen>(this, &UTradeScreen::HandleClose);
}

void UTradeScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();

	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());

	const AStructure* Ship = Cast<AStructure>(Controller->GetPawn());
	const AStructure* Station = Ship->GetLocation()->GetDockStructure();

	const UStructureInventory* ShipInventory = Ship->GetInventory();
	const UStructureInventory* StationInventory = Station->GetInventory();

	TSet Combined(ShipInventory->GetItems());
	Combined.Append(StationInventory->GetItems());
	
	TArray<UObject*> Objects;
	for(UItem* Item : Combined)
	{
		Objects.Add(UTradeEntryObject::New(Item, Ship->GetInventory(), Station->GetInventory()));
	}
	ListView->SetListItems(Objects);
	
	ShipCargoBar->SetFill(FVector2D(FMath::Max(ShipInventory->GetTotalVolume01(), ShipInventory->GetTotalMass01()), 1));
	StationCargoBar->SetFill(FVector2D(FMath::Max(StationInventory->GetTotalVolume01(), StationInventory->GetTotalMass01()), 1));
}

UWidget* UTradeScreen::NativeGetDesiredFocusTarget() const
{
	return CloseButton;
}

void UTradeScreen::HandleClose()
{
	DeactivateWidget();
}
