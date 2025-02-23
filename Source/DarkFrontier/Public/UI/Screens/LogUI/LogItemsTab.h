// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "LogItemsTab.generated.h"

class UItemInfo;
class UItemEntry;
class UCommonButtonBase;
class UListBox;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogItemsTab : public UTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> ItemListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UItemInfo> ItemInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UItemEntry> EntryClass;

	virtual void NativeConstruct() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
