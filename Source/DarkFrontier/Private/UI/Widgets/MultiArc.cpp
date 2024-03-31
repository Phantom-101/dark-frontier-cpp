// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/MultiArc.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "UI/Widgets/Arc.h"

void UMultiArc::ClearArcs() const
{
	ArcOverlay->ClearChildren();
}

UArc* UMultiArc::AddArc()
{
	UArc* Arc = CreateWidget<UArc>(this, ArcClass);
	UOverlaySlot* ArcSlot = ArcOverlay->AddChildToOverlay(Arc);
	ArcSlot->SetHorizontalAlignment(HAlign_Fill);
	ArcSlot->SetVerticalAlignment(VAlign_Fill);
	return Arc;
}

void UMultiArc::RemoveArc(UArc* InArc) const
{
	ArcOverlay->RemoveChild(InArc);
}

void UMultiArc::RemoveArcAt(const int32 Index) const
{
	ArcOverlay->RemoveChildAt(Index);
}
