// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStack.h"
#include "UObject/Object.h"
#include "ItemList.generated.h"

DECLARE_MULTICAST_DELEGATE(FItemListChanged)

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UItemList : public UObject
{
	GENERATED_BODY()

protected:

	// TODO consider removing keys when their quantity is 0
	// Currently getting items will omit those with 0 quantity from the result list
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<TObjectPtr<UItem>, int> Quantities;

public:
	
	FItemListChanged OnChanged;

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems() const;

	// TODO have these take const pointers instead
	UFUNCTION(BlueprintCallable)
	int GetQuantity(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	int HasQuantity(UItem* Item, int Quantity) const;

	UFUNCTION(BlueprintCallable)
	virtual bool SetQuantity(UItem* Item, int Quantity);
	
	UFUNCTION(BlueprintCallable)
	virtual bool AddQuantity(UItem* Item, int Quantity);

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveQuantity(UItem* Item, int Quantity);

	UFUNCTION(BlueprintCallable)
	float GetTotalVolume() const;
	
	UFUNCTION(BlueprintCallable)
	float GetVolume(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	float GetTotalMass() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMass(UItem* Item) const;

	UFUNCTION(BlueprintCallable)
	bool HasList(UItemList* Other) const;

	UFUNCTION(BlueprintCallable)
	virtual bool SetList(UItemList* Other);

	UFUNCTION(BlueprintCallable)
	virtual bool AddList(UItemList* Other);

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveList(UItemList* Other);

};
