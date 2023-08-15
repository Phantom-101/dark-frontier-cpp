// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Structures/Structure.h"

TOptional<FUIInputConfig> UGameUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		const FVector ScaledRotateInput = PlayerStructure->RotateAddInput * 200;
		UWidgetLayoutLibrary::SlotAsCanvasSlot(TurnIndicator)->SetPosition(FVector2D(ScaledRotateInput.Z, ScaledRotateInput.Y));
	}
}
