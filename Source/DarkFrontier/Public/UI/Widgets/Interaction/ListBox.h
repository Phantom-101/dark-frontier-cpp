// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ListBox.generated.h"

class UCommonListView;

DECLARE_MULTICAST_DELEGATE_OneParam(FChanged, UObject*)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UListBox : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	FChanged OnChanged;

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonListView> OptionList;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UObject>> Options;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UObject> CurrentOption;

	TFunction<UWidget* (UObject*)> OptionBuilder;

public:

	void SetOptions(const TArray<UObject*>& InOptions);

	void SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial);

	void SetCurrentOption(UObject* Option);

	void SetBuilder(const TFunction<UWidget* (UObject*)>& Builder);

	bool IsCurrentOptionValid() const;

	UObject* GetCurrentOption();

private:

	void Rebuild();
	
};
