// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StationUI/StationUI.h"
#include "CommonButtonBase.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLocation.h"

void UStationUI::NativeConstruct()
{
	Super::NativeConstruct();

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

void UStationUI::HandleUndock() const
{
	const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	const AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	Player->GetLocation()->ExitDock();
}
