// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Trade/TradeEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Items/Item.h"
#include "Libraries/TradeFunctionLibrary.h"
#include "Structures/StructureInventory.h"

UTradeEntryObject* UTradeEntryObject::New(UItem* Item, UStructureInventory* Inventory, UStructureInventory* Other)
{
	check(Item != nullptr);
	check(Inventory != nullptr);
	check(Other != nullptr);

	UTradeEntryObject* Object = NewObject<UTradeEntryObject>();
	Object->Item = Item;
	Object->Inventory = Inventory;
	Object->Other = Other;
	return Object;
}

void UTradeEntry::NativeConstruct()
{
	Super::NativeConstruct();

	BuyButton->OnClicked().Clear();
	BuyButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleBuy);
	SellButton->OnClicked().Clear();
	SellButton->OnClicked().AddUObject<UTradeEntry>(this, &UTradeEntry::HandleSell);
}

void UTradeEntry::Init(UItem* InItem, UStructureInventory* InInventory, UStructureInventory* InOther)
{
	Item = InItem;
	Inventory = InInventory;
	Other = InOther;

	IconImage->SetBrushFromTexture(Item->Icon);
	NameText->SetText(Item->Name);
}

void UTradeEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	const UTradeEntryObject* Object = Cast<UTradeEntryObject>(ListItemObject);
	check(Object != nullptr);
	Init(Object->Item, Object->Inventory, Object->Other);
}

void UTradeEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(Item == nullptr)
	{
		return;
	}

	if(!IsValid(Inventory) || !IsValid(Other))
	{
		return;
	}

	ShipText->SetText(FText::FromString(FString::FromInt(Inventory->GetQuantity(Item))));
	StationText->SetText(FText::FromString(FString::FromInt(Other->GetQuantity(Item))));
	BuyText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), UTradeFunctionLibrary::GetUnitSellPrice(Other, Item))));
	SellText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), UTradeFunctionLibrary::GetUnitBuyPrice(Other, Item))));
}

void UTradeEntry::HandleBuy()
{
}

void UTradeEntry::HandleSell()
{
}
