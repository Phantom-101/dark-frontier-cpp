// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureDamage.h"
#include "TurretPayload.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTurretPayload : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FStructureDamage Damage;

	UPROPERTY()
	class UFiringPoint* FiringPoint;

	UPROPERTY()
	class AStructure* Target;
	
};
