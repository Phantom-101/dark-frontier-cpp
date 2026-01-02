// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"
#include "Environment/Asteroid.h"
#include "Items/ItemPod.h"
#include "Sectors/Portal.h"
#include "Sectors/SectorRoot.h"
#include "Structures/Structure.h"

ASector::ASector()
{
	Root = CreateDefaultSubobject<USectorRoot>("Root");
	SetRootComponent(Root);
}

const FVector2D& ASector::GetPosition() const
{
	return Position;
}

const FLinearColor& ASector::GetColor() const
{
	return Color;
}

const TSet<TObjectPtr<UTargetable>>& ASector::GetTargets() const
{
	return Targets;
}

TSet<TObjectPtr<ASector>> ASector::GetConnections() const
{
	TSet<TObjectPtr<ASector>> Connections;
	for(const APortal* Portal : Portals)
	{
		const USectorLocation* Destination = ACCESS_COMPONENT(Portal->GetDestination(), SectorLocation);
		if(IsValid(Destination) && IsValid(Destination->GetSector()) && Destination->GetSector() != this)
		{
			Connections.Add(Destination->GetSector());
		}
	}
	return Connections;
}

void ASector::Register(USectorLocation* Location)
{
	Locations.Add(Location);

	AActor* Actor = Location->GetOwner();
	REGISTER_ACTOR(Actor, AStructure, Structures);
	REGISTER_ACTOR(Actor, AAsteroid, Asteroids);
	REGISTER_ACTOR(Actor, AItemPod, ItemPods);
	REGISTER_ACTOR(Actor, APortal, Portals);
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
