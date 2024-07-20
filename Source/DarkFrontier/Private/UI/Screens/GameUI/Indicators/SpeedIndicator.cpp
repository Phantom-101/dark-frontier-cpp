// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/SpeedIndicator.h"
#include "CommonTextBlock.h"
#include "Structures/Indications/SpeedIndication.h"

void USpeedIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const USpeedIndication* Speed = Cast<USpeedIndication>(Indication);
	SpeedText->SetText(FText::FromString(FString::Printf(TEXT("%d m/s"), FMath::RoundToInt(Speed->GetSpeed() / 100))));
}
