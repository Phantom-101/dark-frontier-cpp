// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StationUI/StationUI.h"
#include "CommonButtonBase.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/StationUI/StationTrade.h"

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

void UStationUI::HandleTrade() const
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	(void)Controller->GetUIBaseWidget()->PushGameMenu<UStationTrade>(StationTradeClass);
}

void UStationUI::HandleUndock()
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	const AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	Player->GetLocation()->ExitDock();
	DeactivateWidget();
}
