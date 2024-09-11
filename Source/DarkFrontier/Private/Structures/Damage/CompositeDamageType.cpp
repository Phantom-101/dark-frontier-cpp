// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/CompositeDamageType.h"

FCompositeDamageEntry::FCompositeDamageEntry()
{
	DamageType = nullptr;
	Ratio = 0;
}

FCompositeDamageEntry::FCompositeDamageEntry(const TSubclassOf<UStructureDamageType> InDamageType, const float InRatio)
{
	DamageType = InDamageType;
	Ratio = InRatio;
}

bool FCompositeDamageEntry::IsValid() const
{
	return DamageType != nullptr && Ratio > 0;
}

float UCompositeDamageType::GetMultiplier(const UStructureAbilitySystemComponent* Target) const
{
	float TotalRatio = 0;
	float Multiplier = 0;
	
	for(const FCompositeDamageEntry& Entry : Entries)
	{
		if(Entry.IsValid())
		{
			TotalRatio += Entry.Ratio;
			Multiplier += Entry.Ratio * Entry.DamageType.GetDefaultObject()->GetMultiplier(Target);
		}
	}

	return TotalRatio == 0 ? 0 : Multiplier / TotalRatio;
}
