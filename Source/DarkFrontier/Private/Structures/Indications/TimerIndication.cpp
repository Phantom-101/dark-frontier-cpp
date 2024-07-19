// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/TimerIndication.h"
#include "Kismet/GameplayStatics.h"

void UTimerIndication::Init(float InDuration)
{
	StartTime = UGameplayStatics::GetTimeSeconds(GetWorld());
	Duration = InDuration;
}

float UTimerIndication::GetElapsedPercent() const
{
	const float CurrentTime = UGameplayStatics::GetTimeSeconds(GetWorld());
	return FMath::Clamp((CurrentTime - StartTime) / Duration, 0, 1);
}
