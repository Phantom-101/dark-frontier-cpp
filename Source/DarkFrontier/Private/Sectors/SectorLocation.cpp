// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/SectorLocation.h"
#include "Macros.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Sectors/Sector.h"
#include "Structures/StructureController.h"

void USectorLocation::BeginPlay()
{
	Super::BeginPlay();

	AStructureController* Controller = UGameFunctionLibrary::GetPlayerController(this);
	if(IsValid(Controller))
	{
		Controller->OnSectorChanged.AddUObject(this, &USectorLocation::UpdateSectorState);
	}

	UpdateSectorState(nullptr);
}

void USectorLocation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AStructureController* Controller = UGameFunctionLibrary::GetPlayerController(this);
	if(IsValid(Controller))
	{
		Controller->OnSectorChanged.RemoveAll(this);
	}
	
	if(IsValid(Sector))
	{
		Sector->Unregister(this);
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
		Sector->Unregister(this);
	}
	Sector = InSector;
	if(IsValid(Sector))
	{
		Sector->Register(this);
	}
	OnSectorChanged.Broadcast(Sector);
	UpdateSectorState(nullptr);
}

FVector USectorLocation::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}

void USectorLocation::SetLocation(const FVector& Location) const
{
	GetOwner()->SetActorLocation(Location);
}

bool USectorLocation::GetInPlayerSector() const
{
	return InPlayerSector;
}

void USectorLocation::UpdateSectorState(ASector* _)
{
	InPlayerSector = Sector == UGameFunctionLibrary::GetPlayerSector(this);
	if(InPlayerSector)
	{
		GetOwner()->SetActorHiddenInGame(false);
		GetOwner()->SetActorEnableCollision(true);
	}
	else
	{
		GetOwner()->SetActorHiddenInGame(true);
		GetOwner()->SetActorEnableCollision(false);
	}
	OnSectorStateChanged.Broadcast();
}
