// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Combatant.h"

UCombatant::UCombatant()
{
}

UCombatant::UCombatant(const int StartingCount, AFaction* Faction)
{
	Count = StartingCount;
	OwningFaction = Faction;
}

UCombatant* UCombatant::GetPreferredTarget(TArray<UCombatant*> Combatants)
{
	if(Combatants.Num() == 0)
	{
		return nullptr;
	}

	UCombatant* Ret = Combatants[0];
	double MaxPreference = GetAttackPreference(Ret);
	for(int i = 1; i < Combatants.Num(); i++)
	{
		const double Preference = GetAttackPreference(Combatants[i]);
		if(Preference > MaxPreference)
		{
			Ret = Combatants[i];
			MaxPreference = Preference;
		}
	}

	return Ret;
}

void UCombatant::AttackTarget(UCombatant* Target)
{
	const double AttackDamage = Attack * GetEffectiveness(Target) * Count * (100 / (100 + Target->Defense)) / Target->Health;
	const double CounterattackDamage = 0.5 * Target->Attack * Target->GetEffectiveness(this) * Target->Count * (100 / (100 + Defense)) / Health;

	Target->Count = FMath::Floor(Target->Count - AttackDamage);
	Count = FMath::Floor(Count - CounterattackDamage);
}

double UCombatant::GetAttackPreference(UCombatant* Combatant)
{
	if(Combatant->Count <= 0)
	{
		// Normal preference values are guaranteed to be positive
		return -1;
	}
	
	const double OutgoingAdvantage = GetEffectiveness(Combatant) * (100 / (100 + Combatant->Defense));
	const double IncomingDisadvantage = Combatant->GetEffectiveness(this) * (100 / (100 + Defense));
	const double NumbersAdvantage = FMath::Sqrt(static_cast<double>(Count) / Combatant->Count);
	return OutgoingAdvantage / IncomingDisadvantage * NumbersAdvantage;
}

double UCombatant::GetEffectiveness(const UCombatant* Combatant)
{
	if(Effectiveness.Contains(Combatant->GetClass()))
	{
		return Effectiveness[Combatant->GetClass()] * BuffMultiplier;
	}

	return BuffMultiplier;
}
