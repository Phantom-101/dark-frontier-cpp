// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemFunctionLibrary.generated.h"

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
};
