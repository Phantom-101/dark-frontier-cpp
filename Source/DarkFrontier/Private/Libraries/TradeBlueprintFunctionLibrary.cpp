// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/TradeBlueprintFunctionLibrary.h"

#include "Log.h"
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

float UTradeBlueprintFunctionLibrary::GetUnitBuyPrice(UStructureInventory* Inventory, UItem* Item)
{
	const int Quantity = Inventory->GetQuantity(Item);
	
	const float RateIn = GetRateIn(Inventory, Item);
	const float RateOut = GetRateOut(Inventory, Item);

	AUniverseGameMode* GameMode = Inventory->GetWorld()->GetAuthGameMode<AUniverseGameMode>();

	return CalculateUnitBuyPrice(Item, Quantity, RateIn, RateOut, GameMode->GetTradeParameters());
}

float UTradeBlueprintFunctionLibrary::CalculateUnitBuyPrice(UItem* Item, const int Quantity, const float RateIn, const float RateOut, UTradeParameters* Parameters)
{
	// If item is mostly an output, reduce buying
	const float RateOffset = -UMath::DivTo0(RateOut, RateIn + RateOut) * Parameters->PriceRateFactor;

	const float ThresholdIn = RateIn * Parameters->PriceQuantityTime;
	const float ThresholdOut = RateOut * Parameters->PriceQuantityTime;

	const float Surplus = Quantity - ThresholdIn; // Negative denotes deficit
	const float Divisor = Surplus >= 0 ? ThresholdOut : ThresholdIn;

	// If there is surplus, reduce buying
	const float QuantityOffset = -FMath::Clamp(UMath::DivTo1(Surplus, Divisor), -1, 1) * Parameters->PriceQuantityFactor;

	UE_LOG(LogDarkFrontier, Log, TEXT("r: %f, q: %f"), RateOffset, QuantityOffset)

	const float Multiplier = Parameters->BuyMultiplierBase + RateOffset + QuantityOffset;
	return Item->Value * Multiplier;
}

float UTradeBlueprintFunctionLibrary::GetUnitSellPrice(UStructureInventory* Inventory, UItem* Item)
{
	const int Quantity = Inventory->GetQuantity(Item);
	
	const float RateIn = GetRateIn(Inventory, Item);
	const float RateOut = GetRateOut(Inventory, Item);

	AUniverseGameMode* GameMode = Inventory->GetWorld()->GetAuthGameMode<AUniverseGameMode>();

	return CalculateUnitSellPrice(Item, Quantity, RateIn, RateOut, GameMode->GetTradeParameters());
}

float UTradeBlueprintFunctionLibrary::CalculateUnitSellPrice(UItem* Item, const int Quantity, const float RateIn, const float RateOut, UTradeParameters* Parameters)
{
	// If item is mostly an input, reduce selling
	const float RateOffset = UMath::DivTo0(RateIn, RateIn + RateOut) * Parameters->PriceRateFactor;

	const float ThresholdIn = RateIn * Parameters->PriceQuantityTime;
	const float ThresholdOut = RateOut * Parameters->PriceQuantityTime;

	const float Surplus = Quantity - ThresholdIn; // Negative denotes deficit
	const float Divisor = Surplus >= 0 ? ThresholdOut : ThresholdIn;

	// If there is surplus, increase selling
	const float QuantityOffset = -FMath::Clamp(UMath::DivTo1(Surplus, Divisor), -1, 1) * Parameters->PriceQuantityFactor;

	UE_LOG(LogDarkFrontier, Log, TEXT("r: %f, q: %f"), RateOffset, QuantityOffset)

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
