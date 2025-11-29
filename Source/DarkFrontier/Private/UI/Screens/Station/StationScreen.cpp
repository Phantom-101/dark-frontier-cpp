// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/StationScreen.h"
#include "CommonButtonBase.h"
#include "Input/CommonBoundActionButton.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/StructureController.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Info/InfoScreen.h"
#include "UI/Screens/Station/Refit/RefitScreen.h"
#include "UI/Screens/Station/Repair/RepairScreen.h"
#include "UI/Screens/Station/Trade/TradeScreen.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UStationScreen::RegisterBindings()
{
	Super::RegisterBindings();

	ShipButton->SetRepresentedAction(BindFunction<UStationScreen>(ShipAction, &UStationScreen::ShipInfo));
	TradeButton->SetRepresentedAction(BindScreen(TradeAction, TradeScreenClass.Get()));
	RepairButton->SetRepresentedAction(BindScreen(RepairAction, RepairScreenClass.Get()));
	RefitButton->SetRepresentedAction(BindScreen(RefitAction, RefitScreenClass.Get()));
	UndockButton->SetRepresentedAction(BindFunction<UStationScreen>(UndockAction, &UStationScreen::UndockPlayer));

	StationButton->SetRepresentedAction(BindFunction<UStationScreen>(StationAction, &UStationScreen::StationInfo));
	HangarButton->SetRepresentedAction(BindFunction<UStationScreen>(HangarAction, &UStationScreen::HangarInfo));
}

UWidget* UStationScreen::NativeGetDesiredFocusTarget() const
{
	return UndockButton;
}

TOptional<FUIInputConfig> UStationScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UStationScreen::ShipInfo()
{
	AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	GUARD(IsValid(Player));
	UInfoScreen* Screen = Cast<UInfoScreen>(FloatScreen(InfoScreenClass, true));
	Screen->SetActor(Player);
}

void UStationScreen::UndockPlayer()
{
	const AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	GUARD(IsValid(Player));
	Player->GetDockable()->ExitDock();
	DeactivateWidget();
}

void UStationScreen::StationInfo()
{
	const AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	GUARD(IsValid(Player));
	UInfoScreen* Screen = Cast<UInfoScreen>(FloatScreen(InfoScreenClass, true));
	Screen->SetActor(Player->GetDockable()->GetDockStructure());
}

void UStationScreen::HangarInfo()
{
	const AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	GUARD(IsValid(Player));
	UInfoScreen* Screen = Cast<UInfoScreen>(FloatScreen(InfoScreenClass, true));
	Screen->SetActorWithInitial(Player->GetDockable()->GetDockStructure(), HangarInfoTabClass);
}
