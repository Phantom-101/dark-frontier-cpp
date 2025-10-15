// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/InfoScreen.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Macros.h"
#include "UI/Screens/Info/InfoTab.h"
#include "UI/Widgets/Interaction/Tabs.h"

void UInfoScreen::NativeConstruct()
{
	Super::NativeConstruct();

	InfoTabs->OnTabChanged.AddUObject<UInfoScreen>(this, &UInfoScreen::HandleTabChanged);
	CloseButton->OnClicked().AddUObject<UInfoScreen>(this, &UInfoScreen::DeactivateWidget);

	HandleTabChanged(InfoTabs->GetTabWidget());
}

TOptional<FUIInputConfig> UInfoScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

AActor* UInfoScreen::GetActor() const
{
	return Actor;
}

void UInfoScreen::SetActor(AActor* InActor)
{
	Actor = InActor;
}

void UInfoScreen::HandleTabChanged(UCommonActivatableWidget* Widget)
{
	GUARD(IsValid(Widget));

	if(Widget->IsA<UInfoTab>())
	{
		Cast<UInfoTab>(Widget)->Init(this);
	}
}
