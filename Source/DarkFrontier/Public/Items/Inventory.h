// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.generated.h"

class UItem;
struct FItemStack;

DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryItemAdded, UItem*, int)
DECLARE_MULTICAST_DELEGATE_OneParam(FInventoryItemRemoved, UItem*)
DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryItemChanged, UItem*, int)

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

	FInventoryItemAdded OnItemAdded;

	FInventoryItemRemoved OnItemRemoved;
	
	FInventoryItemChanged OnItemChanged;

	UFUNCTION(BlueprintCallable)
	TArray<FItemStack> GetStacks();

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems();

	UFUNCTION(BlueprintCallable)
	int GetQuantity();

	UFUNCTION(BlueprintCallable)
	int GetItemQuantity(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetVolume();

	UFUNCTION(BlueprintCallable)
	float GetItemVolume(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetVolumeRemaining();

	UFUNCTION(BlueprintCallable)
	float GetMass();

	UFUNCTION(BlueprintCallable)
	float GetItemMass(UItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetMassRemaining();

	UFUNCTION(BlueprintCallable)
	bool CanFit(int ExtraVolume, int ExtraMass);
	
	UFUNCTION(BlueprintCallable)
	bool AddItems(UItem* Item, int Quantity);

	UFUNCTION(BlueprintCallable)
	bool RemoveItems(UItem* Item, int Quantity);
	
};
