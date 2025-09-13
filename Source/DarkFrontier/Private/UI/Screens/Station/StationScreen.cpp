// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/StationScreen.h"
#include "CommonButtonBase.h"
#include "Input/CommonBoundActionButton.h"
#include "Structures/StructureController.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Station/Refit/RefitScreen.h"
#include "UI/Screens/Station/Repair/RepairScreen.h"
#include "UI/Screens/Station/Trade/TradeScreen.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UStationScreen::RegisterBindings()
{
	Super::RegisterBindings();

	TradeButton->SetRepresentedAction(BindScreen(TradeAction, TradeScreenClass.Get()));
	RepairButton->SetRepresentedAction(BindScreen(RepairAction, RepairScreenClass.Get()));
	RefitButton->SetRepresentedAction(BindScreen(RefitAction, RefitScreenClass.Get()));
	UndockButton->SetRepresentedAction(BindFunction<UStationScreen>(UndockAction, &UStationScreen::UndockPlayer));
}

UWidget* UStationScreen::NativeGetDesiredFocusTarget() const
{
	return UndockButton;
}

TOptional<FUIInputConfig> UStationScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UStationScreen::UndockPlayer()
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	const AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	Player->GetDockable()->ExitDock();
	DeactivateWidget();
}
