// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Menu/MenuScreen.h"
#include "CommonButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuScreen::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked().Clear();
	QuitButton->OnClicked().AddUObject<UMenuScreen>(this, &UMenuScreen::HandleQuit);
	LoadButton->OnClicked().Clear();
	LoadButton->OnClicked().AddUObject<UMenuScreen>(this, &UMenuScreen::HandleLoad);
	SaveButton->OnClicked().Clear();
	SaveButton->OnClicked().AddUObject<UMenuScreen>(this, &UMenuScreen::HandleSave);
	OptionsButton->OnClicked().Clear();
	OptionsButton->OnClicked().AddUObject<UMenuScreen>(this, &UMenuScreen::HandleOptions);
	ResumeButton->OnClicked().Clear();
	ResumeButton->OnClicked().AddUObject<UMenuScreen>(this, &UMenuScreen::HandleResume);
}

void UMenuScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();

	GetWorld()->GetFirstPlayerController()->SetPause(true);
}

void UMenuScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if(APlayerController* Controller = GetWorld()->GetFirstPlayerController(); IsValid(Controller))
	{
		Controller->SetPause(false);
	}
}

UWidget* UMenuScreen::NativeGetDesiredFocusTarget() const
{
	return ResumeButton;
}

TOptional<FUIInputConfig> UMenuScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UMenuScreen::HandleQuit() const
{
	// TODO replace with quitting to main menu
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMenuScreen::HandleLoad()
{
}

void UMenuScreen::HandleSave()
{
}

void UMenuScreen::HandleOptions()
{
}

void UMenuScreen::HandleResume()
{
	DeactivateWidget();
}
