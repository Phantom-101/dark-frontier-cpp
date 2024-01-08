// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ConfirmationModal.generated.h"

DECLARE_MULTICAST_DELEGATE(FConfirmationModalActionTaken)
// Include an additional dynamic delegate to allow blueprint access
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConfirmationModalActionTakenDynamic);

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UConfirmationModal : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	FConfirmationModalActionTaken OnConfirmed;
	
	UPROPERTY(BlueprintAssignable)
	FConfirmationModalActionTakenDynamic OnConfirmedDynamic;

	FConfirmationModalActionTaken OnCanceled;

	UPROPERTY(BlueprintAssignable)
	FConfirmationModalActionTakenDynamic OnCanceledDynamic;

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

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetText(FText NewHeader, FText NewBody) const;

private:

	void OnConfirmButtonClicked();

	void OnCancelButtonClicked();
	
};
