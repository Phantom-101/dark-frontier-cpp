// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartAbilityButtonList.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartAbilityButtonList : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> ButtonList;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructurePartClass> ClassObj;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
