// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Tabs.generated.h"

class UTabEntry;
class UWidgetSwitcher;
class UListBox;
class UTab;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTabs : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> TabListBox;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> TabSwitcher;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UTabEntry> TabEntryClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UTab>> TabClasses;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UTab>> Tabs;

	virtual void NativeConstruct() override;

private:

	void HandleTabSelected(UObject* Tab) const;
	
};
