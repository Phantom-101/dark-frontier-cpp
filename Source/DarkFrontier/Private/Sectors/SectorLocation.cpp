// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/SectorLocation.h"
#include "Macros.h"
#include "Sectors/Sector.h"

void USectorLocation::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(Sector))
	{
		Sector->Register(GetOwner());
	}
	OnSectorChanged.Broadcast(Sector);
}

void USectorLocation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(IsValid(Sector))
	{
		Sector->Unregister(GetOwner());
	}
	Sector = nullptr;
	OnSectorChanged.Broadcast(Sector);
}

ASector* USectorLocation::GetSector() const
{
	return Sector;
}

void USectorLocation::SetSector(ASector* InSector)
{
	GUARD(Sector != InSector);
	if(IsValid(Sector))
	{
		Sector->Unregister(GetOwner());
	}
	Sector = InSector;
	if(IsValid(Sector))
	{
		Sector->Register(GetOwner());
	}
	OnSectorChanged.Broadcast(Sector);
}

FVector USectorLocation::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}

void USectorLocation::SetLocation(const FVector& Location) const
{
	GetOwner()->SetActorLocation(Location);
}
