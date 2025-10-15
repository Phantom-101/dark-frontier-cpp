// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/ItemFunctionLibrary.h"
#include "InstancedStruct.h"
#include "Items/Item.h"
#include "Items/ItemFragment.h"
#include "Items/ItemHandle.h"
#include "Items/ItemList.h"
#include "Items/ItemQuantity.h"

TOptional<FLinearColor> UItemFunctionLibrary::GetColor(const UItem* Item)
{
	for(const TInstancedStruct<FItemFragment>& Fragment : Item->GetFragments())
	{
		if(Fragment.GetScriptStruct() == FItemColor::StaticStruct())
		{
			return Fragment.GetPtr<FItemColor>()->Color;
		}
	}
	return TOptional<FLinearColor>();
}

TArray<UItemHandle*> UItemFunctionLibrary::ToHandles(UItemList* List)
{
	TArray<UItemHandle*> Handles;
	for(UItem* Item : List->GetItems())
	{
		Handles.Add(UItemHandle::New(List, Item));
	}
	return Handles;
}

TArray<UItemQuantity*> UItemFunctionLibrary::ToQuantities(const UItemList* List)
{
	TArray<UItemQuantity*> Quantities;
	for(UItem* Item : List->GetItems())
	{
		Quantities.Add(UItemQuantity::New(Item, List->GetQuantity(Item)));
	}
	return Quantities;
}
