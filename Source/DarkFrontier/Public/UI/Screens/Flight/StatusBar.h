// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StatusBar.generated.h"

class UMenuScreen;
class ULogScreen;
class UCommonButtonBase;
class UWidgetSwitcher;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStatusBar : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> TextSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> StatusText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NotificationText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> BalanceText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LogButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> MenuButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> PauseButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<ULogScreen> LogScreenClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UMenuScreen> MenuScreenClass;

	virtual void NativeConstruct() override;

private:

	void HandleLog() const;

	void HandleMenu() const;
	
};
