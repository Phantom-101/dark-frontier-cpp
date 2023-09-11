// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ConfirmationModal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

void UConfirmationModal::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UConfirmationModal>(this, &UConfirmationModal::OnConfirmButtonClicked);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UConfirmationModal>(this, &UConfirmationModal::OnCancelButtonClicked);
}

void UConfirmationModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UConfirmationModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UConfirmationModal::NativeOnHandleBackAction()
{
	OnCancelButtonClicked();
	return true;
}

void UConfirmationModal::SetText(FText NewHeader, FText NewBody) const
{
	HeaderText->SetText(NewHeader);
	BodyText->SetText(NewBody);
}

void UConfirmationModal::OnConfirmButtonClicked()
{
	DeactivateWidget();
	OnConfirmed.Broadcast();
	OnConfirmedDynamic.Broadcast();
}

void UConfirmationModal::OnCancelButtonClicked()
{
	DeactivateWidget();
	OnCanceled.Broadcast();
	OnCanceledDynamic.Broadcast();
}
