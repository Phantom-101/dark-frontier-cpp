// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Portal.h"
#include "Components/SphereComponent.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Targetable.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;
	
	Trigger = CreateDefaultSubobject<USphereComponent>("Trigger");
	Trigger->SetSphereRadius(5000);
	SetRootComponent(Trigger);
	
	Location = CreateDefaultSubobject<USectorLocation>("Location");
	Targetable = CreateDefaultSubobject<UTargetable>("Targetable");
}

void APortal::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor : Actors)
	{
		USectorLocation* User = ACCESS_COMPONENT(Actor, SectorLocation);
		if(IsValid(User))
		{
			Transfer(User);
		}
	}
}

USectorLocation* APortal::GetSectorLocation() const
{
	return Location;
}

UTargetable* APortal::GetTargetable() const
{
	return Targetable;
}

void APortal::Transfer(const TObjectPtr<USectorLocation>& User) const
{
	const USectorLocation* Comp = ACCESS_COMPONENT(Destination, SectorLocation);
	GUARD(IsValid(Comp));

	FVector TargetLocation = Comp->GetLocation();

	// If the destination is a portal, offset the location along its forward axis
	// This prevents the user from being within its transfer range
	const APortal* Portal = Cast<APortal>(Destination);
	if(IsValid(Portal))
	{
		TargetLocation += Portal->GetActorForwardVector() * 10000;
	}

	// TODO use some generalized bound checking function to determine forward offset

	User->SetSector(Comp->GetSector());
	User->SetLocation(TargetLocation);
}
