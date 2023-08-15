// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CompatibleSectionEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UCompatibleSectionEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotList;

public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
