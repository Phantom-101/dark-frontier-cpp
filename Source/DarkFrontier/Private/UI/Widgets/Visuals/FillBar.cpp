// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/FillBar.h"
#include "CommonBorder.h"

void UFillBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateStyle();
	UpdateRender();
}

void UFillBar::SetStyle(const TSubclassOf<UCommonBorderStyle>& InStyle)
{
	ForegroundStyle = InStyle;
	UpdateStyle();
}

void UFillBar::SetStart(const FVector2D InStart)
{
	Start = InStart;
	UpdateRender();
}

void UFillBar::SetFill(const FVector2D InFill)
{
	Fill = InFill;
	UpdateRender();
}

void UFillBar::UpdateStyle() const
{
	Foreground->SetStyle(ForegroundStyle);
}

void UFillBar::UpdateRender() const
{
	Foreground->SetRenderTransformPivot(Start);
	Foreground->SetRenderScale(Fill);
}
