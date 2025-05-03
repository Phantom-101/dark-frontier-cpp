// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDamageType.h"

float UStructureDamageType::Evaluate(const UTargetGroup* TargetGroup) const
{
	if(DamageMultiplierMap.Contains(TargetGroup))
	{
		return DamageMultiplierMap[TargetGroup];
	}

	return 1;
}
