// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogFactionEntry.h"
#include "CommonTextBlock.h"
#include "Factions/Faction.h"
#include "UI/Widgets/Visuals/RelationBar.h"

void ULogFactionEntry::Init(AFaction* InFaction)
{
	Faction = InFaction;

	NameText->SetText(Faction->GetFactionName());
	RelationBar->Init(Faction);
}

void ULogFactionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<AFaction>(ListItemObject));
}
