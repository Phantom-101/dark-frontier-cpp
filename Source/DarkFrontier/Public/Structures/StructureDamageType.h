// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "StructureDamageType.generated.h"

struct FDamageEvent;
class UTargetGroup;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ShieldMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float HullMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PartMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MiningPower = 0.1;

	UFUNCTION(BlueprintPure)
	static const UStructureDamageType* GetDamageTypeFromEvent(const FDamageEvent& DamageEvent);
	
};
