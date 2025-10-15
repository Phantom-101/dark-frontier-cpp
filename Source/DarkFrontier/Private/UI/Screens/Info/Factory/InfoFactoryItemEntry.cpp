// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Factory/InfoFactoryItemEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Components/Image.h"
#include "Items/Item.h"
#include "Items/ItemQuantity.h"

void UInfoFactoryItemEntry::Init(UItemQuantity* InQuantity)
{
	Quantity = InQuantity;
	GUARD(IsValid(Quantity) && IsValid(Quantity->Item));

	IconImage->SetBrushFromTexture(Quantity->Item->Icon);
	QuantityText->SetText(FText::FromString(FString::FromInt(Quantity->Quantity)));
}

void UInfoFactoryItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UItemQuantity>(ListItemObject));
}
