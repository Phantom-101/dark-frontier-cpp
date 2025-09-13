// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"
#include "Environment/Asteroid.h"
#include "Items/ItemPod.h"
#include "Structures/Structure.h"

ASector::ASector()
{
	PrimaryActorTick.bCanEverTick = true;
}

const TArray<TScriptInterface<ITargetable>>& ASector::GetTargets()
{
	return Targets;
}

void ASector::Register(AActor* Actor)
{
	Actors.Add(Actor);

	TryRegister<AStructure>(Actor, Structures);
	TryRegister<AAsteroid>(Actor, Asteroids);
	TryRegister<AItemPod>(Actor, ItemPods);

	if(Actor->Implements<ITargetable>())
	{
		Targets.Add(TScriptInterface<ITargetable>(Actor));
	}
}

void ASector::Unregister(AActor* Actor)
{
	Actors.Remove(Actor);

	TryUnregister<AStructure>(Actor, Structures);
	TryUnregister<AAsteroid>(Actor, Asteroids);
	TryUnregister<AItemPod>(Actor, ItemPods);

	if(Actor->Implements<ITargetable>())
	{
		Targets.Remove(TScriptInterface<ITargetable>(Actor));
	}
}
