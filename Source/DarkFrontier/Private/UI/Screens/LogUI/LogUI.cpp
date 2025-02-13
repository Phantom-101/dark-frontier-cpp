// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogUI.h"
#include "CommonButtonBase.h"

void ULogUI::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<ULogUI>(this, &ULogUI::HandleClose);
}

void ULogUI::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* ULogUI::NativeGetDesiredFocusTarget() const
{
	return CloseButton;
}

void ULogUI::HandleClose()
{
	DeactivateWidget();
}
