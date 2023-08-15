// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "InputModifierAccumulator.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UInputModifierAccumulator : public UInputModifier
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings, Config)
	double ActivationThreshold;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings, Config)
	FVector AccumulationLimit;

protected:

	FInputActionValue Accumulation;
	
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
	
};
