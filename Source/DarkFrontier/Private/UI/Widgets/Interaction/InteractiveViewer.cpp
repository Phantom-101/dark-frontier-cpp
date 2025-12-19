// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/InteractiveViewer.h"
#include "CommonButtonBase.h"
#include "Macros.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"

void UInteractiveViewer::NativeConstruct()
{
	Super::NativeConstruct();
	ResetButton->OnClicked().AddUObject(this, &UInteractiveViewer::Reset);
	ZoomInButton->OnClicked().AddUObject(this, &UInteractiveViewer::ZoomIn);
	ZoomOutButton->OnClicked().AddUObject(this, &UInteractiveViewer::ZoomOut);
	UpdateZoom(FVector2D::ZeroVector);
}

void UInteractiveViewer::Reset()
{
	ZoomLevel = 0;
	UpdateZoom(FVector2D::ZeroVector);
	
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ContentSlot);
	PanelSlot->SetPosition(FVector2D::ZeroVector);
}

void UInteractiveViewer::ZoomIn()
{
	const FVector2D Center = GetCenter();
	ZoomLevel = FMath::Clamp(ZoomLevel + 1, MinZoomLevel, MaxZoomLevel);
	UpdateZoom(Center);
}

void UInteractiveViewer::ZoomOut()
{
	const FVector2D Center = GetCenter();
	ZoomLevel = FMath::Clamp(ZoomLevel - 1, MinZoomLevel, MaxZoomLevel);
	UpdateZoom(Center);
}

FReply UInteractiveViewer::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
}

void UInteractiveViewer::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	OutOperation = NewObject<UPanOperation>();
	OutOperation->OnDragged.AddDynamic(this, &UInteractiveViewer::HandlePan);
}

FVector2D UInteractiveViewer::GetCenter() const
{
	const UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ContentSlot);
	return PanelSlot->GetPosition() / GetScaleFactor();
}

void UInteractiveViewer::UpdateZoom(const FVector2D& Focal) const
{
	ContentSlot->SetRenderScale(FVector2D(GetScaleFactor()));

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ContentSlot);
	PanelSlot->SetPosition(Focal * GetScaleFactor());
}

float UInteractiveViewer::GetScaleFactor() const
{
	return FMath::Pow(ZoomFactor, ZoomLevel);
}

void UInteractiveViewer::HandlePan(UDragDropOperation* Operation)
{
	const UPanOperation* Pan = Cast<UPanOperation>(Operation);
	GUARD(IsValid(Pan));
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ContentSlot);
	PanelSlot->SetPosition(PanelSlot->GetPosition() + Pan->CursorDelta);
}

void UPanOperation::Dragged_Implementation(const FPointerEvent& PointerEvent)
{
	CursorDelta = PointerEvent.GetCursorDelta();
	Super::Dragged_Implementation(PointerEvent);
}
