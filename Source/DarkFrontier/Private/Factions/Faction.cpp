// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Faction.h"

AFaction::AFaction()
{
}

void AFaction::BeginPlay()
{
	EconomicFocus = FMath::Clamp(EconomicFocus, -1, 1);
	EconomicIntegration = FMath::Clamp(EconomicIntegration, -1, 1);
	EconomicDiversity = FMath::Clamp(EconomicDiversity, -1, 1);
	EconomicExpansion = FMath::Clamp(EconomicExpansion, -1, 1);

	MilitaryFocus = FMath::Clamp(MilitaryFocus, -1, 1);
	MilitaryIntegration = FMath::Clamp(MilitaryIntegration, -1, 1);
	MilitaryDiversity = FMath::Clamp(MilitaryDiversity, -1, 1);
	MilitaryExpansion = FMath::Clamp(MilitaryExpansion, -1, 1);
}

FText AFaction::GetFactionName() const
{
	return FactionName;
}

double AFaction::GetBalance() const
{
	return Balance;
}

void AFaction::SetBalance(const double Target)
{
	Balance = Target;
}

double AFaction::ChangeBalance(const double Delta)
{
	SetBalance(Balance + Delta);
	return Balance;
}

double AFaction::GetRelation(AFaction* Other) const
{
	if(Other == this)
	{
		return 1;
	}
	
	if(Relations.Contains(Other))
	{
		return Relations[Other];
	}
	
	return 0;
}

void AFaction::SetRelation(AFaction* Other, double Target)
{
	Target = FMath::Clamp(Target, -1, 1);
	Relations[Other] = Target;
	Other->Relations[this] = Target;
}

double AFaction::ChangeRelation(AFaction* Other, const double Delta)
{
	const double Target = GetRelation(Other) + Delta;
	SetRelation(Other, Target);
	return Target;
}
