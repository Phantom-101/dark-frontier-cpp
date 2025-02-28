// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "LogPropertyTab.generated.h"

class UStructureEntry;
class UCommonButtonBase;
class UCommonTextBlock;
class UListBox;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogPropertyTab : public UTab
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> StructureListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UStructureEntry> EntryClass;
	
	virtual void NativeConstruct() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
