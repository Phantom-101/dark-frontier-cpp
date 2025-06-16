// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/StationScreen.h"
#include "CommonButtonBase.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Station/Trade/StationTradeScreen.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UStationScreen::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton->OnClicked().Clear();
	TradeButton->OnClicked().AddUObject<UStationScreen>(this, &UStationScreen::HandleTrade);
	UndockButton->OnClicked().Clear();
	UndockButton->OnClicked().AddUObject<UStationScreen>(this, &UStationScreen::HandleUndock);
}

void UStationScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UStationScreen::NativeGetDesiredFocusTarget() const
{
	return UndockButton;
}

TOptional<FUIInputConfig> UStationScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UStationScreen::HandleTrade() const
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	Controller->GetGameScreens()->GetGameStack()->AddWidget<UStationTradeScreen>(TradeScreenClass.Get());
}

void UStationScreen::HandleUndock()
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	const AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	Player->GetLocation()->ExitDock();
	DeactivateWidget();
}
