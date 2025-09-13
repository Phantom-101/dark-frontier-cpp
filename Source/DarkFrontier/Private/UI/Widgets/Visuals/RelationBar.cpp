// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/RelationBar.h"
#include "Factions/Faction.h"
#include "Libraries/GameFunctionLibrary.h"

void URelationBar::Init(const AFaction* InFaction)
{
	AFaction* PlayerFaction = UGameFunctionLibrary::GetPlayerFaction(this);
	if(InFaction == PlayerFaction)
	{
		SetForegroundStyle(PlayerStyle);
		SetBar(1);
	}
	else
	{
		const float Relation = InFaction->GetRelation(PlayerFaction);
		SetForegroundStyle(Relation > 0 ? PositiveStyle : NegativeStyle);
		SetBar(Relation);
	}
}

void URelationBar::Init(const AFaction* InReference, AFaction* InOther)
{
	const AFaction* PlayerFaction = UGameFunctionLibrary::GetPlayerFaction(this);
	if(InReference == PlayerFaction)
	{
		SetForegroundStyle(PlayerStyle);
		SetBar(1);
	}
	else
	{
		const float Relation = InReference->GetRelation(InOther);
		SetForegroundStyle(Relation > 0 ? PositiveStyle : NegativeStyle);
		SetBar(Relation);
	}
}

void URelationBar::SetBar(const float Relation)
{
	FillHorizontal(Relation / 2 + 0.5, 0.5);
}
