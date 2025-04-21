// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/SimpleDamageType.h"

float USimpleDamageType::Evaluate(const UTargetGroup* TargetGroup) const
{
	if(DamageMultiplierMap.Contains(TargetGroup))
	{
		return DamageMultiplierMap[TargetGroup];
	}

	return 1;
}
