// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Modals/ConfirmationModal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

void UConfirmationModal::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UConfirmationModal>(this, &UConfirmationModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UConfirmationModal>(this, &UConfirmationModal::HandleCancel);
}

void UConfirmationModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

void UConfirmationModal::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	OnConfirmed.Clear();
	OnCanceled.Clear();
}

UWidget* UConfirmationModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UConfirmationModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UConfirmationModal::SetText(const FText NewHeader, const FText NewBody) const
{
	HeaderText->SetText(NewHeader);
	BodyText->SetText(NewBody);
}

void UConfirmationModal::HandleConfirm()
{
	OnConfirmed.Broadcast();
	DeactivateWidget();
}

void UConfirmationModal::HandleCancel()
{
	OnCanceled.Broadcast();
	DeactivateWidget();
}
