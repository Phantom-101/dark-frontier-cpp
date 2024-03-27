// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructureGameplayAbilityListView.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureGameplayAbilityListView : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> AbilityList;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
