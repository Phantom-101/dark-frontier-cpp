// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/SimpleDamageType.h"
#include "Structures/StructureAbilitySystemComponent.h"

float USimpleDamageType::GetHullMultiplier(const UStructureAbilitySystemComponent* Target) const
{
	return FMath::Exp(-Target->GetNumericAttribute(HullResistanceAttribute));
}

float USimpleDamageType::GetShieldMultiplier(const UStructureAbilitySystemComponent* Target) const
{
	return FMath::Exp(-Target->GetNumericAttribute(ShieldResistanceAttribute));
}
