// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/CompositeDamageType.h"

FCompositeDamageEntry::FCompositeDamageEntry()
{
	DamageType = nullptr;
	Weight = 0;
}

FCompositeDamageEntry::FCompositeDamageEntry(const TSubclassOf<UStructureDamageType>& InDamageType, const float InWeight)
{
	DamageType = InDamageType;
	Weight = InWeight;
}

bool FCompositeDamageEntry::IsValid() const
{
	return DamageType != nullptr && Weight > 0;
}

float UCompositeDamageType::Evaluate(const UTargetGroup* TargetGroup) const
{
	float TotalWeight = 0;
	float Multiplier = 0;
	
	for(const FCompositeDamageEntry& Entry : Entries)
	{
		if(Entry.IsValid())
		{
			TotalWeight += Entry.Weight;
			Multiplier += Entry.Weight * Entry.DamageType.GetDefaultObject()->Evaluate(TargetGroup);
		}
	}

	return TotalWeight == 0 ? 1 : Multiplier / TotalWeight;
}
