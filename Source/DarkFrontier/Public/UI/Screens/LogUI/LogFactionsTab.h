﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "LogFactionsTab.generated.h"

class UFactionInfo;
class UFactionEntry;
class UCommonButtonBase;
class UCommonTextBlock;
class UListBox;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogFactionsTab : public UTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> FactionListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFactionInfo> FactionInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UFactionEntry> EntryClass;

	virtual void NativeConstruct() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
