// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/AnnotatedArc.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "UI/Widgets/Visuals/Arc.h"

void UAnnotatedArc::NativePreConstruct()
{
	Super::NativePreConstruct();

	UCanvasPanelSlot* ArcPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Arc);
	ArcPanelSlot->SetSize(FVector2D(Size, Size));

	Arc->SetThickness(Thickness / Size);
	Arc->SetStartAndLength(Direction + Gap / 2, 1 - Gap);

	UCanvasPanelSlot* ContentPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ContentSlot);
	ContentPanelSlot->SetPosition(FVector2D(FMath::Sin(Direction * 2 * PI), FMath::Cos(Direction * 2 * PI)) * Size / 2);

	Arc->SetColor(Color);
}
