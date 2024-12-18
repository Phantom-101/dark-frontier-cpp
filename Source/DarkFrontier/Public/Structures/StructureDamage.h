// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureDamage.generated.h"

class UStructureDamageType;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureDamage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)	
	TSubclassOf<UStructureDamageType> DamageType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Amount;

	FStructureDamage();

	FStructureDamage(const TSubclassOf<UStructureDamageType>& InDamageType, float InAmount);

	bool IsValid() const;

};
