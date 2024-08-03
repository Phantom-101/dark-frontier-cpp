// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ItemList.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemList : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UListView> ItemList;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UItem> SelectedItem;

public:

	UInventory* GetInventory() const;

	void SetInventory(UInventory* InInventory);

	UItem* GetSelectedItem() const;

	void SetSelectedItem(UItem* InItem);

private:

	void UpdateAll() const;

	void AddItem(UItem* Item, int Initial) const;

	void RemoveItem(UItem* Item) const;
	
};
