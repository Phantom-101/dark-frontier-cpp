// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemFunctionLibrary.generated.h"

class UItemQuantity;
class UItemList;
class UItemHandle;
class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static TOptional<FLinearColor> GetColor(const UItem* Item);

	UFUNCTION(BlueprintPure)
	static TArray<UItemHandle*> ToHandles(UItemList* List);

	UFUNCTION(BlueprintPure)
	static TArray<UItemQuantity*> ToQuantities(const UItemList* List);
	
};
