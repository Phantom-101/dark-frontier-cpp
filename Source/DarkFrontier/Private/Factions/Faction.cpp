// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Faction.h"
#include "EngineUtils.h"
#include "Structures/Structure.h"
#include "Structures/StructureIndices.h"

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

ASector* AFaction::GetHome() const
{
	return Home;
}

float AFaction::GetBalance() const
{
	return Balance;
}

void AFaction::SetBalance(const float Target)
{
	Balance = Target;
}

float AFaction::ChangeBalance(const float Delta)
{
	SetBalance(Balance + Delta);
	return Balance;
}

float AFaction::GetRelation(AFaction* Other) const
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

void AFaction::SetRelation(AFaction* Other, float Target)
{
	Target = FMath::Clamp(Target, -1, 1);
	Relations[Other] = Target;
	Other->Relations[this] = Target;
}

float AFaction::ChangeRelation(AFaction* Other, const float Delta)
{
	const float Target = GetRelation(Other) + Delta;
	SetRelation(Other, Target);
	return Target;
}

float AFaction::GetPower() const
{
	float Power = 0;
	for(TActorIterator<AStructure> Itr(GetWorld()); Itr; ++Itr)
	{
		if(Itr->GetOwningFaction() == this)
		{
			Power += Itr->GetIndices()->GetParts().Num();
		}
	}
	return Power;
}

float AFaction::GetReputation()
{
	float Total = 0;
	int Count = 0;
	for(TActorIterator<AFaction> Itr(GetWorld()); Itr; ++Itr)
	{
		Total += Itr->GetRelation(this);
		Count++;
	}
	return Total / Count;
}
