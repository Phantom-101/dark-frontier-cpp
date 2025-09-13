// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/SectorLocation.h"
#include "Macros.h"
#include "Sectors/Sector.h"

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

void USectorLocation::UpdateSector()
{
	// TODO potentially change this to not involve sector change events
	ASector* Temp = Sector;
	SetSector(nullptr);
	SetSector(Temp);
}

FVector USectorLocation::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}
