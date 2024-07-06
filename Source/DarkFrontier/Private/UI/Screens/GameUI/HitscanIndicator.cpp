// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/HitscanIndicator.h"
#include "Components/SizeBox.h"
#include "Structures/ProgressIndication.h"

void UHitscanIndicator::NativePreConstruct()
{
	Super::NativePreConstruct();

	SizeBox->SetWidthOverride(MaxSize);
	SizeBox->SetHeightOverride(MaxSize);
}

void UHitscanIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const float Multiplier = FMath::Clamp(1 - Indication->Progress, 0, 1);
	SizeBox->SetWidthOverride(MaxSize * Multiplier);
	SizeBox->SetHeightOverride(MaxSize * Multiplier);
}
