// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogUniverseMapConnection.h"
#include "Macros.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Sectors/Sector.h"

void ULogUniverseMapConnection::Init(ASector* InFrom, ASector* InTo)
{
	From = InFrom;
	To = InTo;
	GUARD(IsValid(From) && IsValid(To));
	
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	PanelSlot->SetAnchors(FAnchors(0.5));
	PanelSlot->SetAlignment(FVector2D(0, 0.5));
	SetRenderTransformPivot(FVector2D(0, 0.5));

	const FVector2D Delta = To->GetPosition() - From->GetPosition();
	PanelSlot->SetSize(FVector2D(Delta.Length() / 2, 10));
	SetRenderTransformAngle(FMath::RadiansToDegrees(FMath::Atan2(Delta.Y, Delta.X)));
}
