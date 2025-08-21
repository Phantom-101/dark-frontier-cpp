// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LogFactionsTab.generated.h"

class UListView;
class ULogFactionInfo;
class UCommonButtonBase;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogFactionsTab : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<ULogFactionInfo> FactionInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual void NativeOnDeactivated() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
