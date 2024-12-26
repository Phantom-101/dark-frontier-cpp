// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ListBoxModal.generated.h"

class UListBox;
class UCommonButtonBase;
class UCommonListView;
class UCommonTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(FConfirmed, UObject*)
DECLARE_MULTICAST_DELEGATE(FCanceled)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UListBoxModal : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	FConfirmed OnConfirmed;

	FCanceled OnCanceled;

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> HeaderText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> ListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;

public:

	void SetOptions(const TArray<UObject*>& InOptions) const;

	void SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial) const;

	void SetCurrentOption(UObject* Option) const;

	void SetBuilder(const TFunction<UWidget* (UObject*)>& Builder) const;

	bool IsCurrentOptionValid() const;

	UObject* GetCurrentOption() const;

private:

	void HandleConfirm();

	void HandleCancel();
	
};
