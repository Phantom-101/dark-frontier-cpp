// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/FactionInfo.h"
#include "Factions/Faction.h"
#include "Sectors/Sector.h"
#include "UI/Screens/LogUI/FactionEntry.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UFactionInfo::Init(AFaction* Faction) const
{
	Header->Init(Faction);
	TypeField->SetContentFromString("Test");
	HomeField->SetContent(GetHomeText(Faction->GetHome()));
	WealthField->SetContent(GetWealthText(Faction->GetBalance()));
	PowerField->SetContent(GetPowerText(Faction->GetPower()));
	ReputationField->SetContent(GetReputationText(Faction->GetReputation()));
}

FText UFactionInfo::GetHomeText(const ASector* Home)
{
	if (Home == nullptr)
	{
		return FText::FromString("None");
	}

	return FText::FromString(Home->GetActorNameOrLabel());
}

FText UFactionInfo::GetWealthText(const float Balance)
{
	if(Balance >= 1000000)
	{
		return FText::FromString("Affluent");
	}
	if(Balance >= 500000)
	{
		return FText::FromString("Comfortable");
	}
	if(Balance >= 100000)
	{
		return FText::FromString("Deprived");
	}
	return FText::FromString("Destitute");
}

FText UFactionInfo::GetPowerText(const float Power)
{
	if(Power >= 100)
	{
		return FText::FromString("Superpower");
	}
	if(Power >= 30)
	{
		return FText::FromString("Strong");
	}
	if(Power >= 10)
	{
		return FText::FromString("Weak");
	}
	return FText::FromString("Feeble");
}

FText UFactionInfo::GetReputationText(const float Reputation)
{
	if(Reputation >= 0.5)
	{
		return FText::FromString("Paragon");
	}
	if(Reputation >= 0.25)
	{
		return FText::FromString("Virtuous");
	}
	if(Reputation >= -0.25)
	{
		return FText::FromString("Neutral");
	}
	if(Reputation >= -0.5)
	{
		return FText::FromString("Controversial");
	}
	return FText::FromString("Evil");
}
