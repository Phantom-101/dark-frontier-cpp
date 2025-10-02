// Fill out your copyright notice in the Description page of Project Settings.

#include "Factions/Affiliation.h"
#include "Macros.h"
#include "Factions/Faction.h"

void UAffiliation::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(Faction))
	{
		Faction->Register(this);
	}
	OnFactionChanged.Broadcast(Faction);
}

void UAffiliation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(IsValid(Faction))
	{
		Faction->Unregister(this);
	}
	Faction = nullptr;
	OnFactionChanged.Broadcast(Faction);
}

AFaction* UAffiliation::GetFaction() const
{
	return Faction;
}

void UAffiliation::SetFaction(AFaction* InFaction)
{
	GUARD(Faction != InFaction);
	if(IsValid(Faction))
	{
		Faction->Unregister(this);
	}
	Faction = InFaction;
	if(IsValid(Faction))
	{
		Faction->Register(this);
	}
	OnFactionChanged.Broadcast(Faction);
}
