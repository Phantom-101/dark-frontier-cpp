// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/StructureDamageType.h"

float UStructureDamageType::GetHullMultiplier(const UStructureAbilitySystemComponent* Target) const
{
	return 1;
}

float UStructureDamageType::GetShieldMultiplier(const UStructureAbilitySystemComponent* Target) const
{
	return 1;
}
