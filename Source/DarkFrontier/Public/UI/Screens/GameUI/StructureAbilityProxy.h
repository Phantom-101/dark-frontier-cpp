// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePart.h"
#include "StructureAbilityProxy.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureAbilityProxy : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void TryActivate();

	UFUNCTION()
	virtual float GetArcLength();
	
};
