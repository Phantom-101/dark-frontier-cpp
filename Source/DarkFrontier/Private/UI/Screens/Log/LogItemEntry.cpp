// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogItemEntry.h"
#include "CommonTextBlock.h"
#include "Items/Item.h"

void ULogItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	
	const UItem* Item = Cast<UItem>(ListItemObject);
	NameText->SetText(Item->Name);
}
