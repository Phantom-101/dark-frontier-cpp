// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UniverseGameMode.generated.h"

class UTradeParameters;
class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AUniverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AUniverseGameMode();

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TObjectPtr<UItem>> ItemList;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTradeParameters> TradeParameters;
	
public:

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItemList();

	UFUNCTION(BlueprintCallable)
	UTradeParameters* GetTradeParameters();
	
};
