// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"
#include "Environment/Asteroid.h"
#include "Items/ItemPod.h"
#include "Sectors/SectorRoot.h"
#include "Structures/Structure.h"

ASector::ASector()
{
	Root = CreateDefaultSubobject<USectorRoot>("Root");
	SetRootComponent(Root);
}

const TSet<TObjectPtr<UTargetable>>& ASector::GetTargets() const
{
	return Targets;
}

void ASector::Register(USectorLocation* Location)
{
	Locations.Add(Location);

	AActor* Actor = Location->GetOwner();
	REGISTER_ACTOR(Actor, AStructure, Structures);
	REGISTER_ACTOR(Actor, AAsteroid, Asteroids);
	REGISTER_ACTOR(Actor, AItemPod, ItemPods);
	REGISTER_COMPONENT_INTERFACE(Actor, Targetable, Targets);
}

void ASector::Unregister(USectorLocation* Location)
{
	Locations.Remove(Location);

	AActor* Actor = Location->GetOwner();
	UNREGISTER_ACTOR(Actor, AStructure, Structures);
	UNREGISTER_ACTOR(Actor, AAsteroid, Asteroids);
	UNREGISTER_ACTOR(Actor, AItemPod, ItemPods);
	UNREGISTER_COMPONENT_INTERFACE(Actor, Targetable, Targets);
}
