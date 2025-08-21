// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LogPropertyTab.generated.h"

class UListView;
class ULogPropertyInfo;
class UCommonButtonBase;
class UCommonTextBlock;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogPropertyTab : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<ULogPropertyInfo> PropertyInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
