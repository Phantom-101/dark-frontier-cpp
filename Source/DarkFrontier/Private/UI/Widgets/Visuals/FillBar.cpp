// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/FillBar.h"
#include "CommonBorder.h"
#include "Macros.h"
#include "Libraries/Math.h"

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

void UFillBar::SetPivot(const FVector2D InPivot)
{
	Pivot = InPivot;
	UpdateFill();
}

void UFillBar::SetFill(const FVector2D InFill)
{
	Fill = InFill;
	UpdateFill();
}

void UFillBar::FillRect(const FVector2D& InStart, const FVector2D& InEnd)
{
	Fill = InEnd - InStart;
	const FVector2D Unfilled = FVector2D::UnitVector - Fill;
	Pivot = FVector2D(UMath::DivTo0(InStart.X, Unfilled.X), UMath::DivTo0(InStart.Y, Unfilled.Y));
	UpdateFill();
}

void UFillBar::FillHorizontal(const float InStart, const float InEnd)
{
	FillRect(FVector2D(InStart, 0), FVector2D(InEnd, 1));
}

void UFillBar::FillVertical(const float InStart, const float InEnd)
{
	FillRect(FVector2D(0, InStart), FVector2D(1, InEnd));
}

void UFillBar::UpdateStyling() const
{
	Background->SetStyle(BackgroundStyle);
	Foreground->SetStyle(ForegroundStyle);
}

void UFillBar::UpdateFill() const
{
	Foreground->SetRenderTransformPivot(Pivot);
	Foreground->SetRenderScale(Fill);
}
