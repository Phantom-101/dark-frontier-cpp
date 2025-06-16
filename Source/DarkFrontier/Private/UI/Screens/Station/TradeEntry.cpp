// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Trade/TradeEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Item.h"
#include "Libraries/TradeBlueprintFunctionLibrary.h"
#include "Structures/StructureInventory.h"

void UTradeEntry::NativeConstruct()
{
	Super::NativeConstruct();

	BuyButton->OnClicked().Clear();
	BuyButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleBuy);
	SellButton->OnClicked().Clear();
	SellButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleSell);
}

void UTradeEntry::Init(UItem* InItem, UStructureInventory* InCurrent, UStructureInventory* InTarget)
{
	Item = InItem;
	Current = InCurrent;
	Target = InTarget;

	IconImage->SetBrushFromTexture(Item->Icon);
	NameText->SetText(Item->Name);
}

void UTradeEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(Item == nullptr)
	{
		return;
	}

	if(!IsValid(Current) || !IsValid(Target))
	{
		return;
	}

	ShipText->SetText(FText::FromString(FString::FromInt(Current->GetQuantity(Item))));
	StationText->SetText(FText::FromString(FString::FromInt(Target->GetQuantity(Item))));
	BuyText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), UTradeBlueprintFunctionLibrary::GetUnitSellPrice(Target, Item))));
	SellText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), UTradeBlueprintFunctionLibrary::GetUnitBuyPrice(Target, Item))));
}

void UTradeEntry::HandleBuy()
{
}

void UTradeEntry::HandleSell()
{
}
