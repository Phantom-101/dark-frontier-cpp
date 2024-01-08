// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartActionEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructurePartActionEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructurePartAction> Action;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ActionButton;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnActionButtonClicked() const;
	
};
