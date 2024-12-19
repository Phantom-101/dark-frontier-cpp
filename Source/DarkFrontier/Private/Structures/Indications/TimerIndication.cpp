// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/TimerIndication.h"

void UTimerIndication::Init(const FTimerHandle InHandle)
{
	TimerHandle = InHandle;
}

float UTimerIndication::GetElapsedPercent() const
{
	if(TimerHandle.IsValid())
	{
		const FTimerManager& Manager = GetWorld()->GetTimerManager();
		return Manager.GetTimerElapsed(TimerHandle) / Manager.GetTimerRate(TimerHandle);
	}

	return 0;
}
