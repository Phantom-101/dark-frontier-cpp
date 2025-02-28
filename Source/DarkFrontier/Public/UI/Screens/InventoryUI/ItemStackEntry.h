// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ItemStackEntry.generated.h"

class UItem;
class UItemStackObject;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UItemStackEntry : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItemStackObject> ItemStack;

public:

	void Init(UItemStackObject* InItemStack);

private:
	
	void UpdateQuantity(UItem* InItem, int InQuantity) const;
	
};
