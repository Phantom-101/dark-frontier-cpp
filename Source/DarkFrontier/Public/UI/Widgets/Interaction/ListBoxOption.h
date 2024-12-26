// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ListBoxOption.generated.h"

class UCommonButtonBase;
class UListBoxOptionParams;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UListBoxOption : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNamedSlot> ContentSlot;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UListBoxOptionParams> Params;

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void HandleSelect() const;
	
};
