// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TradePriceTest.h"
#include "Log.h"
#include "Game/UniverseGameMode.h"
#include "Libraries/TradeBlueprintFunctionLibrary.h"

void UTradePriceTest::BeginPlay()
{
	Super::BeginPlay();

	UTradeParameters* Params = GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();

	for(int Quantity = 0; Quantity <= 100; Quantity += 50)
	{
		for(float RateIn = 0; RateIn <= 1; RateIn += 0.5)
		{
			for(float RateOut = 0; RateOut <= 1; RateOut += 0.5)
			{
				UE_LOG(LogDarkFrontier, Log, TEXT("q: %d, i: %f, o: %f"), Quantity, RateIn, RateOut);
				UE_LOG(LogDarkFrontier, Log, TEXT("Station buys for %f"), UTradeBlueprintFunctionLibrary::CalculateUnitBuyPrice(Item, Quantity, RateIn, RateOut, Params));
				UE_LOG(LogDarkFrontier, Log, TEXT("Station sells for %f"), UTradeBlueprintFunctionLibrary::CalculateUnitSellPrice(Item, Quantity, RateIn, RateOut, Params));
			}
		}
	}
}
