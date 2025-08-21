// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableEntry.h"
#include "TabEntry.generated.h"

class UTab;
class UCommonTextBlock;
class UImage;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTabEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UTab> Tab;

public:

	void Init(UTab* InTab);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

};
