// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Indicators/HitscanIndicator.h"
#include "Components/SizeBox.h"
#include "Structures/Indications/TimerIndication.h"
#include "Structures/Structure.h"

void UHitscanIndicator::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(IsValid(SizeBox))
	{
		SizeBox->SetWidthOverride(MaxSize);
		SizeBox->SetHeightOverride(MaxSize);
	}
}

void UHitscanIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UTimerIndication* Timer = Cast<UTimerIndication>(Indication);
	const float Multiplier = 1 - Timer->GetElapsedPercent();
	
	if(Multiplier == 0)
	{
		Timer->GetStructure()->RemoveIndication(Timer);
	}
	else
	{
		SizeBox->SetWidthOverride(MaxSize * Multiplier);
		SizeBox->SetHeightOverride(MaxSize * Multiplier);
	}
}
