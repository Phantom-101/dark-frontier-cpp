// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "StructureDamageType.generated.h"

class UStructureAbilitySystemComponent;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureDamageType : public UDamageType
{
	GENERATED_BODY()

public:

	virtual float GetMultiplier(const UStructureAbilitySystemComponent* Target) const;
	
};
