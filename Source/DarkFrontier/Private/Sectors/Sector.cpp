// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"
#include "Structures/Structure.h"

ASector::ASector()
{
	PrimaryActorTick.bCanEverTick = true;
}

const TArray<TScriptInterface<ITargetable>>& ASector::GetTargets()
{
	return Targets;
}

void ASector::RegisterStructure(AStructure* Structure)
{
	Structures.Add(Structure);
	Targets.Add(TScriptInterface<ITargetable>(Structure));
}

void ASector::UnregisterStructure(AStructure* Structure)
{
	Structures.Remove(Structure);
	Targets.Remove(TScriptInterface<ITargetable>(Structure));
}
