// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TradeBlueprintFunctionLibrary.generated.h"

class UTradeParameters;
class UStructureInventory;
class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTradeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static float GetBuyPrice(UStructureInventory* Inventory, UItem* Item, int BuyQuantity);

	UFUNCTION(BlueprintCallable)
	static float GetUnitBuyPrice(UStructureInventory* Inventory, UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	static float CalculateUnitBuyPrice(UItem* Item, int Quantity, float RateIn, float RateOut, UTradeParameters* Parameters);

	UFUNCTION(BlueprintCallable)
	static float GetSellPrice(UStructureInventory* Inventory, UItem* Item, int SellQuantity);
	
	UFUNCTION(BlueprintCallable)
	static float GetUnitSellPrice(UStructureInventory* Inventory, UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	static float CalculateUnitSellPrice(UItem* Item, int Quantity, float RateIn, float RateOut, UTradeParameters* Parameters);

	UFUNCTION(BlueprintCallable)
	static float GetRateIn(UStructureInventory* Inventory, UItem* Item);

	UFUNCTION(BlueprintCallable)
	static float GetRateOut(UStructureInventory* Inventory, UItem* Item);
	
};
