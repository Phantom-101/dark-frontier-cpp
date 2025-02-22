// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UniverseGameMode.generated.h"

class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AUniverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TObjectPtr<UItem>> AllowedItems;

public:

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetAllowedItems();
	
};
