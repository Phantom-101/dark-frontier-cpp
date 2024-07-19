// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.generated.h"

class UItem;
struct FItemStack;

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UInventory : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxVolume = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxMass = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FItemStack> ItemStacks;

public:

	UFUNCTION(BlueprintCallable)
	TArray<FItemStack> GetStacks();

	UFUNCTION(BlueprintCallable)
	int GetQuantity();

	UFUNCTION(BlueprintCallable)
	int GetItemQuantity(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetValue();

	UFUNCTION(BlueprintCallable)
	float GetItemValue(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetVolume();

	UFUNCTION(BlueprintCallable)
	float GetItemVolume(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetMass();

	UFUNCTION(BlueprintCallable)
	float GetItemMass(UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool CanFit(int ExtraVolume, int ExtraMass);
	
	UFUNCTION(BlueprintCallable)
	bool AddItems(UItem* Item, int Quantity, float Value);

	UFUNCTION(BlueprintCallable)
	bool AddStack(const FItemStack& InStack);

	UFUNCTION(BlueprintCallable)
	bool RemoveItems(UItem* Item, int Quantity, float& Value);

	UFUNCTION(BlueprintCallable)
	bool RemoveStack(const FItemStack& InStack);
	
};
