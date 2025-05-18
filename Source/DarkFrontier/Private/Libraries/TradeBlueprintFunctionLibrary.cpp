// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/TradeBlueprintFunctionLibrary.h"
#include "Game/TradeParameters.h"
#include "Game/UniverseGameMode.h"
#include "Items/Item.h"
#include "Items/ItemList.h"
#include "Items/Recipe.h"
#include "Libraries/Math.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureProduction.h"

float UTradeBlueprintFunctionLibrary::GetBuyPrice(UStructureInventory* Inventory, UItem* Item, int BuyQuantity)
{
	check(Inventory != nullptr)
	check(Item != nullptr)

	if(!ensure(BuyQuantity >= 0))
	{
		BuyQuantity = 0;
	}

	const int Quantity = Inventory->GetQuantity(Item);

	const float RateIn = GetRateIn(Inventory, Item);
	const float RateOut = GetRateOut(Inventory, Item);

	UTradeParameters* Parameters = Inventory->GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();

	float Price = 0;
	for(int Current = 0; Current < BuyQuantity; Current++)
	{
		Price += CalculateUnitBuyPrice(Item, Quantity + Current, RateIn, RateOut, Parameters);
	}

	return Price;
}

float UTradeBlueprintFunctionLibrary::GetUnitBuyPrice(UStructureInventory* Inventory, UItem* Item)
{
	return GetBuyPrice(Inventory, Item, 1);
}

float UTradeBlueprintFunctionLibrary::CalculateUnitBuyPrice(UItem* Item, int Quantity, float RateIn, float RateOut, UTradeParameters* Parameters)
{
	check(Item != nullptr)
	check(Parameters != nullptr)
	
	if(!ensure(Quantity >= 0))
	{
		Quantity = 0;
	}
	
	if(!ensure(RateIn >= 0))
	{
		RateIn = 0;
	}
	
	if(!ensure(RateOut >= 0))
	{
		RateOut = 0;
	}
	
	// If item is mostly an output, reduce buying
	const float RateOffset = -UMath::DivTo0(RateOut, RateIn + RateOut) * Parameters->PriceRateFactor;

	const float ThresholdIn = RateIn * Parameters->PriceQuantityTime;
	const float ThresholdOut = RateOut * Parameters->PriceQuantityTime;

	const float Surplus = Quantity - ThresholdIn; // Negative denotes deficit
	const float Divisor = Surplus >= 0 ? ThresholdOut : ThresholdIn;

	// If there is surplus, reduce buying
	const float QuantityOffset = -FMath::Clamp(UMath::DivTo1(Surplus, Divisor), -1, 1) * Parameters->PriceQuantityFactor;

	const float Multiplier = Parameters->BuyMultiplierBase + RateOffset + QuantityOffset;
	return Item->Value * Multiplier;
}

float UTradeBlueprintFunctionLibrary::GetSellPrice(UStructureInventory* Inventory, UItem* Item, int SellQuantity)
{
	check(Inventory != nullptr)
	check(Item != nullptr)

	if(!ensure(SellQuantity >= 0))
	{
		SellQuantity = 0;
	}

	const int Quantity = Inventory->GetQuantity(Item);

	if(!ensure(SellQuantity <= Quantity))
	{
		SellQuantity = Quantity;
	}

	const float RateIn = GetRateIn(Inventory, Item);
	const float RateOut = GetRateOut(Inventory, Item);

	UTradeParameters* Parameters = Inventory->GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();

	float Price = 0;
	for(int Current = 0; Current < SellQuantity; Current++)
	{
		Price += CalculateUnitSellPrice(Item, Quantity - Current, RateIn, RateOut, Parameters);
	}

	return Price;
}

float UTradeBlueprintFunctionLibrary::GetUnitSellPrice(UStructureInventory* Inventory, UItem* Item)
{
	return GetSellPrice(Inventory, Item, 1);
}

float UTradeBlueprintFunctionLibrary::CalculateUnitSellPrice(UItem* Item, int Quantity, float RateIn, float RateOut, UTradeParameters* Parameters)
{
	check(Item != nullptr)
	check(Parameters != nullptr)
	
	if(!ensure(Quantity >= 0))
	{
		Quantity = 0;
	}
	
	if(!ensure(RateIn >= 0))
	{
		RateIn = 0;
	}
	
	if(!ensure(RateOut >= 0))
	{
		RateOut = 0;
	}
	
	// If item is mostly an input, reduce selling
	const float RateOffset = UMath::DivTo0(RateIn, RateIn + RateOut) * Parameters->PriceRateFactor;

	const float ThresholdIn = RateIn * Parameters->PriceQuantityTime;
	const float ThresholdOut = RateOut * Parameters->PriceQuantityTime;

	const float Surplus = Quantity - ThresholdIn; // Negative denotes deficit
	const float Divisor = Surplus >= 0 ? ThresholdOut : ThresholdIn;

	// If there is surplus, increase selling
	const float QuantityOffset = -FMath::Clamp(UMath::DivTo1(Surplus, Divisor), -1, 1) * Parameters->PriceQuantityFactor;

	const float Multiplier = 1 + RateOffset + QuantityOffset;
	return Item->Value * Multiplier;
}

float UTradeBlueprintFunctionLibrary::GetRateIn(UStructureInventory* Inventory, UItem* Item)
{
	float Rate = 0;
	for(const UStructureProduction* Production : Inventory->GetStructure()->GetLayout()->GetFacilities<UStructureProduction>())
	{
		const URecipe* Recipe = Production->GetRecipe();
		if(Recipe->Inputs->GetItems().Contains(Item))
		{
			Rate += Recipe->Inputs->GetQuantity(Item) / Recipe->Time;
		}
	}
	return Rate;
}

float UTradeBlueprintFunctionLibrary::GetRateOut(UStructureInventory* Inventory, UItem* Item)
{
	float Rate = 0;
	for(const UStructureProduction* Production : Inventory->GetStructure()->GetLayout()->GetFacilities<UStructureProduction>())
	{
		const URecipe* Recipe = Production->GetRecipe();
		if(Recipe->Outputs->GetItems().Contains(Item))
		{
			Rate += Recipe->Outputs->GetQuantity(Item) / Recipe->Time;
		}
	}
	return Rate;
}
