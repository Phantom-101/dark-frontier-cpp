// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Faction.h"
#include "EngineUtils.h"
#include "Game/UniverseGameMode.h"
#include "Items/Item.h"
#include "Structures/Structure.h"
#include "Structures/StructureLayout.h"

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

const TSet<TObjectPtr<UAffiliation>>& AFaction::GetAffiliated() const
{
	return Affiliated;
}

const TSet<TObjectPtr<AStructure>>& AFaction::GetProperty() const
{
	return Property;
}

void AFaction::Register(UAffiliation* Affiliation)
{
	Affiliated.Add(Affiliation);
	REGISTER_ACTOR(Affiliation->GetOwner(), AStructure, Property);
}

void AFaction::Unregister(UAffiliation* Affiliation)
{
	Affiliated.Remove(Affiliation);
	UNREGISTER_ACTOR(Affiliation->GetOwner(), AStructure, Property);
}

float AFaction::GetPower() const
{
	float Power = 0;
	for(const AStructure* Structure : Property)
	{
		Power += Structure->GetLayout()->GetParts().Num();
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
