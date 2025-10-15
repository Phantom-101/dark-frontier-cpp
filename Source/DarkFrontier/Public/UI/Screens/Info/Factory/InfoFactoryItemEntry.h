// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "InfoFactoryItemEntry.generated.h"

class UCommonTextBlock;
class UImage;
class UItemQuantity;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoFactoryItemEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItemQuantity> Quantity;

public:

	void Init(UItemQuantity* InQuantity);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

};
