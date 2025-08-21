// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDamage.h"
#include "Structures/StructureDamageType.h"

FStructureDamage::FStructureDamage()
{
	DamageType = nullptr;
	Amount = 0;
}

FStructureDamage::FStructureDamage(const TSubclassOf<UStructureDamageType>& InDamageType, const float InAmount)
{
	DamageType = InDamageType;
	Amount = InAmount;
}

bool FStructureDamage::IsValid() const
{
	return DamageType != nullptr && Amount >= 0;
}
