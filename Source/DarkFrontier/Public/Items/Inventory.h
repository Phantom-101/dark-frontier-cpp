// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemList.h"
#include "Inventory.generated.h"

class UItem;

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UInventory : public UItemList
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxVolume = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxMass = 0;
	
public:
	
	UFUNCTION(BlueprintCallable)
	int FitsQuantity(const UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	virtual bool SetQuantity(UItem* Item, int Quantity) override;
	
	UFUNCTION(BlueprintCallable)
	virtual bool AddQuantity(UItem* Item, int Quantity) override;

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveQuantity(UItem* Item, int Quantity) override;

	UFUNCTION(BlueprintCallable)
	float GetMaxVolume() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalVolume01() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeVolume() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeVolume01() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMaxMass() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalMass01() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeMass() const;

	UFUNCTION(BlueprintCallable)
	float GetFreeMass01() const;
	
	UFUNCTION(BlueprintCallable)
	bool FitsList(const UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	virtual bool SetList(UItemList* Other) override;

	UFUNCTION(BlueprintCallable)
	virtual bool AddList(UItemList* Other) override;

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveList(UItemList* Other) override;
	
};
