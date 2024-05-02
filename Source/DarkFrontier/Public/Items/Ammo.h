// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Structures/StructureDamage.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DARKFRONTIER_API UAmmo : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FStructureDamage BaseDamage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TurretCooldownMultiplier = 1;
	
};
