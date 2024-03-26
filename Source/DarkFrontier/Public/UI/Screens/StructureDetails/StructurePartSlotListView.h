// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartSlotListView.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartSlotListView : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotList;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
