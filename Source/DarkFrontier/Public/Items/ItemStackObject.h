// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemStackObject.generated.h"

class UItem;
class UInventory;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemStackObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;
	
};
