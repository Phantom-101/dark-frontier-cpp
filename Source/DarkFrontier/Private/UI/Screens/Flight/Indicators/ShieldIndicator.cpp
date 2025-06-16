// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Indicators/ShieldIndicator.h"
#include "Components/Image.h"
#include "Curves/CurveLinearColor.h"
#include "Structures/Indications/ShieldIndication.h"

void UShieldIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const UShieldIndication* Shield = Cast<UShieldIndication>(Indication);
	const float Percent = Shield->GetShieldPercent();
	const float R = ColorCurve->FloatCurves[0].Eval(Percent);
	const float G = ColorCurve->FloatCurves[1].Eval(Percent);
	const float B = ColorCurve->FloatCurves[2].Eval(Percent);
	const float A = ColorCurve->FloatCurves[3].Eval(Percent);
	Icon->SetColorAndOpacity(FLinearColor(R, G, B, A));
}
