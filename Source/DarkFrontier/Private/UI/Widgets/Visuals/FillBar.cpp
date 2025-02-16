// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/FillBar.h"
#include "CommonBorder.h"

void UFillBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateStyling();
	UpdateFill();
}

void UFillBar::SetBackgroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle)
{
	BackgroundStyle = InStyle;
	UpdateStyling();
}

void UFillBar::SetForegroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle)
{
	ForegroundStyle = InStyle;
	UpdateStyling();
}

void UFillBar::SetStart(const FVector2D InStart)
{
	Start = InStart;
	UpdateFill();
}

void UFillBar::SetFill(const FVector2D InFill)
{
	Fill = InFill;
	UpdateFill();
}

void UFillBar::UpdateStyling() const
{
	Background->SetStyle(BackgroundStyle);
	Foreground->SetStyle(ForegroundStyle);
}

void UFillBar::UpdateFill() const
{
	Foreground->SetRenderTransformPivot(Start);
	Foreground->SetRenderScale(Fill);
}
