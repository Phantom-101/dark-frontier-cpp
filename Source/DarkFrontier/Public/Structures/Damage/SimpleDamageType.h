// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "StructureDamageType.h"
#include "SimpleDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API USimpleDamageType : public UStructureDamageType
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayAttribute HullResistanceAttribute;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayAttribute ShieldResistanceAttribute;

public:

	virtual float GetHullMultiplier(const UStructureAbilitySystemComponent* Target) const override;

	virtual float GetShieldMultiplier(const UStructureAbilitySystemComponent* Target) const override;
	
};
