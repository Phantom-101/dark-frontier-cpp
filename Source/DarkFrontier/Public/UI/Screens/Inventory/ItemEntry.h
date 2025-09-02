// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "ItemEntry.generated.h"

class UItem;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UItemEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

public:

	void Init(const UItem* Item) const;

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
