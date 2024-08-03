// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemEntry.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UItem> Item;

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnEntryReleased() override;

private:
	
	void OnSelected();

	void UpdateQuantity(UItem* InItem, int InQuantity);
	
};
