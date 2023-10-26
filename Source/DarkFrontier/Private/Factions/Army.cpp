// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Army.h"

UArmy::UArmy()
{
}

UArmy::UArmy(const int StartingCount, AFaction* Faction)
{
	Count = StartingCount;
	OwningFaction = Faction;
}

UArmy* UArmy::GetPreferredTarget(TArray<UArmy*> Armies)
{
	if(Armies.Num() == 0)
	{
		return nullptr;
	}

	UArmy* Ret = Armies[0];
	double MaxPreference = GetAttackPreference(Ret);
	for(int i = 1; i < Armies.Num(); i++)
	{
		const double Preference = GetAttackPreference(Armies[i]);
		if(Preference > MaxPreference)
		{
			Ret = Armies[i];
			MaxPreference = Preference;
		}
	}

	return Ret;
}

void UArmy::AttackTarget(UArmy* Target)
{
	const double AttackDamage = Attack * GetEffectiveness(Target) * Count * (100 / (100 + Target->Defense)) / Target->Health;
	const double CounterattackDamage = 0.5 * Target->Attack * Target->GetEffectiveness(this) * Target->Count * (100 / (100 + Defense)) / Health;

	Target->Count = FMath::Floor(Target->Count - AttackDamage);
	Count = FMath::Floor(Count - CounterattackDamage);
}

double UArmy::GetAttackPreference(UArmy* Army)
{
	if(Army->Count <= 0)
	{
		// Normal preference values are guaranteed to be positive
		return -1;
	}
	
	const double OutgoingAdvantage = GetEffectiveness(Army) * (100 / (100 + Army->Defense));
	const double IncomingDisadvantage = Army->GetEffectiveness(this) * (100 / (100 + Defense));
	const double NumbersAdvantage = FMath::Sqrt(static_cast<double>(Count) / Army->Count);
	return OutgoingAdvantage / IncomingDisadvantage * NumbersAdvantage;
}

double UArmy::GetEffectiveness(const UArmy* Army)
{
	if(Effectiveness.Contains(Army->GetClass()))
	{
		return Effectiveness[Army->GetClass()] * BuffMultiplier;
	}

	return BuffMultiplier;
}
