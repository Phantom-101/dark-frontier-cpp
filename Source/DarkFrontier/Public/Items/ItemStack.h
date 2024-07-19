// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStack.generated.h"

class UItem;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FItemStack
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Quantity = 0;

	/**
	 * Interpreted as total values for game stacks and weights for recipe stacks
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value = 0;

	FItemStack();
	
	FItemStack(UItem* InItem, int InQuantity, double InValue);

	float GetValuePerItem() const;

	float GetVolume() const;

	float GetMass() const;

	bool IsValid() const;

	bool operator==(const FItemStack& Other) const;
	
};
