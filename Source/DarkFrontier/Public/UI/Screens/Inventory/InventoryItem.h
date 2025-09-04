// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class UItem;
class UInventory;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;

	static UInventoryItem* New(UInventory* InInventory, UItem* InItem);
	
};
