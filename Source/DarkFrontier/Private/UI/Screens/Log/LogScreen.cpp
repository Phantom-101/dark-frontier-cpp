// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogScreen.h"
#include "CommonButtonBase.h"

void ULogScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<ULogScreen>(this, &ULogScreen::HandleClose);
}

void ULogScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* ULogScreen::NativeGetDesiredFocusTarget() const
{
	return CloseButton;
}

TOptional<FUIInputConfig> ULogScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void ULogScreen::HandleClose()
{
	DeactivateWidget();
}
