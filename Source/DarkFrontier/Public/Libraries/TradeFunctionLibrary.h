// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TradeFunctionLibrary.generated.h"

class UTradeParameters;
class UStructureInventory;
class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTradeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static float GetBuyPrice(UStructureInventory* Inventory, UItem* Item, int BuyQuantity);

	UFUNCTION(BlueprintPure)
	static float GetUnitBuyPrice(UStructureInventory* Inventory, UItem* Item);
	
	UFUNCTION(BlueprintPure)
	static float CalculateUnitBuyPrice(UItem* Item, int Quantity, float RateIn, float RateOut, const UTradeParameters* Parameters);

	UFUNCTION(BlueprintPure)
	static float GetSellPrice(UStructureInventory* Inventory, UItem* Item, int SellQuantity);
	
	UFUNCTION(BlueprintPure)
	static float GetUnitSellPrice(UStructureInventory* Inventory, UItem* Item);
	
	UFUNCTION(BlueprintPure)
	static float CalculateUnitSellPrice(UItem* Item, int Quantity, float RateIn, float RateOut, const UTradeParameters* Parameters);

	UFUNCTION(BlueprintPure)
	static float GetRateIn(UStructureInventory* Inventory, UItem* Item);

	UFUNCTION(BlueprintPure)
	static float GetRateOut(UStructureInventory* Inventory, UItem* Item);

	UFUNCTION(BlueprintPure)
	static float GetHullRepairPrice(float Damage, const UTradeParameters* Parameters);

	UFUNCTION(BlueprintPure)
	static float GetShieldRepairPrice(float Damage, const UTradeParameters* Parameters);

	// TODO use part price instead
	UFUNCTION(BlueprintPure)
	static float GetPartRepairPrice(float Damage, const UTradeParameters* Parameters);
	
};
