// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CompatibleStructurePartEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UCompatibleStructurePartEntry : public UCommonUserWidget, public IUserObjectListEntry
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
