// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LogItemsTab.generated.h"

class UListView;
class ULogItemInfo;
class UCommonButtonBase;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogItemsTab : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<ULogItemInfo> ItemInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
