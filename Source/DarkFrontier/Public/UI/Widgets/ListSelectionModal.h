// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ListSelectionModal.generated.h"

class UCommonButtonBase;
class UCommonListView;
class UCommonTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(FConfirmed, UObject*)
DECLARE_MULTICAST_DELEGATE(FCanceled)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UListSelectionModal : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	FConfirmed OnConfirmed;

	FCanceled OnCanceled;

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> HeaderText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonListView> SelectionList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UObject>> Options;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UObject> CurrentOption;

	TFunction<UWidget* (UObject*)> OptionBuilder;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;

public:

	void SetOptions(const TArray<UObject*>& InOptions);

	void SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial);

	void SetCurrentOption(UObject* Option);

	void SetBuilder(const TFunction<UWidget* (UObject*)>& Builder);

	UObject* GetCurrentOption();

private:

	void Rebuild();

	void HandleConfirm();

	void HandleCancel();
	
};
