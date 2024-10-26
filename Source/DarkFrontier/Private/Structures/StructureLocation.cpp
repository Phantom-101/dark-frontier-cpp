// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLocation.h"
#include "Sectors/Sector.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"

UStructureLocation* UStructureLocation::CreateLocation(AStructure* Structure)
{
	UStructureLocation* Location = Structure->CreateDefaultSubobject<UStructureLocation>("Location");
	
	return Location;
}

AStructure* UStructureLocation::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}

ASector* UStructureLocation::GetSector() const
{
	return Sector;
}

bool UStructureLocation::EnterSector(ASector* Target)
{
	if(Target == nullptr || Target == Sector)
	{
		return false;
	}

	ExitSector();

	Sector = Target;
	Sector->RegisterStructure(GetStructure());

	GetStructure()->UpdateTickLevel();
	
	return true;
}

bool UStructureLocation::ExitSector()
{
	if(Sector == nullptr)
	{
		return false;
	}

	Sector->UnregisterStructure(GetStructure());
	Sector = nullptr;
	return true;
}

AStructure* UStructureLocation::GetDockee() const
{
	return Dockee;
}

UStructureDock* UStructureLocation::GetDock() const
{
	return Dock;
}

bool UStructureLocation::EnterDock(UStructureDock* Target)
{
	if(Target == nullptr || !Dock->ConfirmDock(GetStructure()))
	{
		return false;
	}

	Dock = Target;
	Dockee = Target->GetOwningStructure();
	Dockee->GetLocation()->Dockers.Add(GetStructure());
	
	GetStructure()->AttachToActor(Dockee, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	return true;
}

bool UStructureLocation::ExitDock()
{
	if(Dock == nullptr || !Dock->ConfirmUnDock(GetStructure()))
	{
		return false;
	}

	Dockee->GetLocation()->Dockers.Remove(GetStructure());
	Dockee = nullptr;
	Dock = nullptr;

	GetStructure()->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	return true;
}

TArray<AStructure*> UStructureLocation::GetDockers() const
{
	return Dockers;
}
