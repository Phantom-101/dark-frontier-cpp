﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StationUI/StationUI.h"
#include "CommonButtonBase.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/GameUIBase.h"
#include "UI/Screens/StationUI/StationTrade.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UStationUI::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton->OnClicked().Clear();
	TradeButton->OnClicked().AddUObject<UStationUI>(this, &UStationUI::HandleTrade);
	UndockButton->OnClicked().Clear();
	UndockButton->OnClicked().AddUObject<UStationUI>(this, &UStationUI::HandleUndock);
}

void UStationUI::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UStationUI::NativeGetDesiredFocusTarget() const
{
	return UndockButton;
}

TOptional<FUIInputConfig> UStationUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UStationUI::HandleTrade() const
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	Controller->GetGameUIBaseWidget()->GetGameStack()->AddWidget<UStationTrade>(StationTradeClass);
}

void UStationUI::HandleUndock()
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	const AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	Player->GetLocation()->ExitDock();
	DeactivateWidget();
}
