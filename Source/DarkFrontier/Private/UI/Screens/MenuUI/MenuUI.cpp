// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/MenuUI/MenuUI.h"
#include "CommonButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked().Clear();
	QuitButton->OnClicked().AddUObject<UMenuUI>(this, &UMenuUI::HandleQuit);
	LoadButton->OnClicked().Clear();
	LoadButton->OnClicked().AddUObject<UMenuUI>(this, &UMenuUI::HandleLoad);
	SaveButton->OnClicked().Clear();
	SaveButton->OnClicked().AddUObject<UMenuUI>(this, &UMenuUI::HandleSave);
	OptionsButton->OnClicked().Clear();
	OptionsButton->OnClicked().AddUObject<UMenuUI>(this, &UMenuUI::HandleOptions);
	ResumeButton->OnClicked().Clear();
	ResumeButton->OnClicked().AddUObject<UMenuUI>(this, &UMenuUI::HandleResume);
}

void UMenuUI::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();

	GetWorld()->GetFirstPlayerController()->SetPause(true);
}

void UMenuUI::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if(APlayerController* Controller = GetWorld()->GetFirstPlayerController(); IsValid(Controller))
	{
		Controller->SetPause(false);
	}
}

UWidget* UMenuUI::NativeGetDesiredFocusTarget() const
{
	return ResumeButton;
}

TOptional<FUIInputConfig> UMenuUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UMenuUI::HandleQuit() const
{
	// TODO replace with quitting to main menu
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMenuUI::HandleLoad()
{
}

void UMenuUI::HandleSave()
{
}

void UMenuUI::HandleOptions()
{
}

void UMenuUI::HandleResume()
{
	DeactivateWidget();
}
