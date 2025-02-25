// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ConfirmationModal.generated.h"

DECLARE_MULTICAST_DELEGATE(FConfirmationModalResolved)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UConfirmationModal : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	FConfirmationModalResolved OnConfirmed;

	FConfirmationModalResolved OnCanceled;

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> HeaderText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> BodyText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual void NativeOnDeactivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetText(FText NewHeader, FText NewBody) const;

private:

	void HandleConfirm();

	void HandleCancel();
	
};
