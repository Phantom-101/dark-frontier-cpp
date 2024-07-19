// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/HullIndicator.h"
#include "Components/Image.h"
#include "Curves/CurveLinearColor.h"
#include "Structures/Indications/HullIndication.h"

void UHullIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const UHullIndication* Hull = Cast<UHullIndication>(Indication);
	const float Percent = Hull->GetHullPercent();
	const float R = ColorCurve->FloatCurves[0].Eval(Percent);
	const float G = ColorCurve->FloatCurves[1].Eval(Percent);
	const float B = ColorCurve->FloatCurves[2].Eval(Percent);
	const float A = ColorCurve->FloatCurves[3].Eval(Percent);
	Icon->SetColorAndOpacity(FLinearColor(R, G, B, A));
}
