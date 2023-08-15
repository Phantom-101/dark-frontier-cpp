// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/InputModifierAccumulator.h"

FInputActionValue UInputModifierAccumulator::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	if(CurrentValue.GetValueType() == EInputActionValueType::Boolean)
	{
		return Super::ModifyRaw_Implementation(PlayerInput, CurrentValue, DeltaTime);
	}

	if(!CurrentValue.Get<FVector>().IsNearlyZero(ActivationThreshold))
	{
		Accumulation = ClampVector((Accumulation + CurrentValue).Get<FVector>(), -AccumulationLimit, AccumulationLimit);
	}
	
	return Accumulation;
}
