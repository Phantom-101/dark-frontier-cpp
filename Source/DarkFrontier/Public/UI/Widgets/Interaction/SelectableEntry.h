// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SelectableEntry.generated.h"

class UListView;
class UStripe;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API USelectableEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<UStripe> Stripe;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UListView> ListView;

	FDelegateHandle OnSelectionChangedHandle;

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnEntryReleased() override;

private:

	void HandleClick() const;

	void UpdateStripe(UObject* Object) const;
	
};
