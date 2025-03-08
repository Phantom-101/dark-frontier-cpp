// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StationUI/TradeEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Structures/Structure.h"

void UTradeEntry::NativeConstruct()
{
	Super::NativeConstruct();

	BuyButton->OnClicked().Clear();
	BuyButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleBuy);
	SellButton->OnClicked().Clear();
	SellButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleSell);
}

void UTradeEntry::Init(UItem* Item, AStructure* Ship, AStructure* Station) const
{
	IconImage->SetBrushFromTexture(Item->Icon);
	NameText->SetText(Item->Name);
	ShipText->SetText(FText::FromString(FString::FromInt(Ship->GetInventory()->GetQuantity(Item))));
	StationText->SetText(FText::FromString(FString::FromInt(Station->GetInventory()->GetQuantity(Item))));
	BuyText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Item->Value)));
	SellText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Item->Value * 1.5)));
}

void UTradeEntry::HandleBuy()
{
}

void UTradeEntry::HandleSell()
{
}
