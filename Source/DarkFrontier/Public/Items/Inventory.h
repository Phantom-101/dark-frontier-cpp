// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.generated.h"

class UItemList;
class AStructure;
class UItem;
struct FItemStack;

DECLARE_MULTICAST_DELEGATE(FInventoryItemsChanged)

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
	TObjectPtr<UItemList> Items;

public:
	
	FInventoryItemsChanged OnItemsChanged;

	UInventory();

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;

	UFUNCTION(BlueprintCallable)
	TArray<FItemStack> GetStacks() const;

	UFUNCTION(BlueprintCallable)
	bool GetStack(UItem* Item, FItemStack& OutStack) const;

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems() const;

	UFUNCTION(BlueprintCallable)
	int GetQuantity(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	int HasQuantity(UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	int FitsQuantity(const UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	void SetQuantity(UItem* Item, int Quantity) const;
	
	UFUNCTION(BlueprintCallable)
	void AddQuantity(UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	void RemoveQuantity(UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	float GetMaxVolume() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalVolume() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalVolume01() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeVolume() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeVolume01() const;
	
	UFUNCTION(BlueprintCallable)
	float GetVolume(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	float GetMaxMass() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalMass() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalMass01() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeMass() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeMass01() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMass(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	UItemList* GetList() const;

	UFUNCTION(BlueprintCallable)
	bool HasList(UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	bool FitsList(const UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	void SetList(UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	void AddList(UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	void RemoveList(UItemList* Other) const;
	
};
