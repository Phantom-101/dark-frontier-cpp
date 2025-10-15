// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Cargo/InfoCargoEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Components/Image.h"
#include "Items/Item.h"
#include "Items/ItemHandle.h"

void UInfoCargoEntry::Init(UItemHandle* InHandle)
{
	Handle = InHandle;
	
	GUARD(IsValid(Handle) && Handle->IsValid());

	IconImage->SetBrushFromTexture(Handle->Item->Icon);
	NameText->SetText(Handle->Item->Name);
}

void UInfoCargoEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UItemHandle>(ListItemObject));
}

void UInfoCargoEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Handle) && Handle->IsValid());

	QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Handle->List->GetQuantity(Handle->Item))));
}
