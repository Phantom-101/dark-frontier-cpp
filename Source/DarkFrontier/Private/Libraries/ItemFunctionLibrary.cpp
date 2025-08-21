// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/ItemFunctionLibrary.h"
#include "InstancedStruct.h"
#include "Items/Item.h"
#include "Items/ItemFragment.h"

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
