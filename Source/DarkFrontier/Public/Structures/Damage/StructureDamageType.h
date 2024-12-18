// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "StructureDamageType.generated.h"

class UAbilitySystemComponent;
class UTargetGroup;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureDamageType : public UDamageType
{
	GENERATED_BODY()

public:

	// TODO only return resistance value and let caller decide how to calculate damage
	virtual float Evaluate(const UTargetGroup* TargetGroup, const UAbilitySystemComponent* Comp) const;
	
};
