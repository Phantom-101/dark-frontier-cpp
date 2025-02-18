// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "LogMailTab.generated.h"

class UMailEntry;
class UCommonButtonBase;
class UCommonTextBlock;
class UListBox;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogMailTab : public UTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> MailListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SubjectText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> BodyText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BackButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UMailEntry> EntryClass;

	virtual void NativeConstruct() override;

private:

	void HandleSelect(UObject* Object) const;

	void HandleBack() const;
	
};
