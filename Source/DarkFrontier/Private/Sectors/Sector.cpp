// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"
#include "Environment/Asteroid.h"
#include "Items/ItemPod.h"
#include "Structures/Structure.h"

const TArray<TObjectPtr<UTargetable>>& ASector::GetTargets()
{
	return Targets;
}

void ASector::Register(AActor* Actor)
{
	Actors.Add(Actor);

	TryRegister<AStructure>(Actor, Structures);
	TryRegister<AAsteroid>(Actor, Asteroids);
	TryRegister<AItemPod>(Actor, ItemPods);

	if(Actor->Implements<UTargetableInterface>())
	{
		Targets.Add(Cast<ITargetableInterface>(Actor)->GetTargetable());
	}
}

void ASector::Unregister(AActor* Actor)
{
	Actors.Remove(Actor);

	TryUnregister<AStructure>(Actor, Structures);
	TryUnregister<AAsteroid>(Actor, Asteroids);
	TryUnregister<AItemPod>(Actor, ItemPods);

	if(Actor->Implements<UTargetableInterface>())
	{
		Targets.Remove(Cast<ITargetableInterface>(Actor)->GetTargetable());
	}
}
