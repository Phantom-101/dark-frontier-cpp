// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TradeParameters.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UTradeParameters : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BuyMultiplierBase = 0.95;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PriceRateFactor = 0.2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PriceQuantityFactor = 0.3;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PriceQuantityTime = 1800;
	
};
