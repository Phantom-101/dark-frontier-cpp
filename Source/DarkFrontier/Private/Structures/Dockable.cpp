// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Dockable.h"
#include "Macros.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"

AStructure* UDockable::GetStructure() const
{
	return GetOwner<AStructure>();
}

UStructureDock* UDockable::GetDock() const
{
	return Dock;
}

AStructure* UDockable::GetDockStructure() const
{
	return Dock->GetOwningStructure();
}

bool UDockable::EnterDock(UStructureDock* Target)
{
	GUARD_RETURN(IsValid(Target) && Target->ConfirmDock(GetStructure()), false);

	GetOwner()->AttachToActor(Target->GetOwningStructure(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	if(Target->Implements<USectorLocationInterface>())
	{
		Cast<ISectorLocationInterface>(Target)->GetSectorLocation()->OnSectorChanged.AddUObject(this, &UDockable::PropagateSector);
	}

	Dock = Target;
	OnDockChanged.Broadcast(Dock);

	return true;
}

bool UDockable::ExitDock()
{
	GUARD_RETURN(IsValid(Dock) && Dock->ConfirmUnDock(GetStructure()), false);

	GetOwner()->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	if(Dock->Implements<USectorLocationInterface>())
	{
		Cast<ISectorLocationInterface>(Dock)->GetSectorLocation()->OnSectorChanged.RemoveAll(this);
	}

	Dock = nullptr;
	OnDockChanged.Broadcast(Dock);

	return true;
}

void UDockable::PropagateSector(ASector* Sector) const
{
	if(GetOwner()->Implements<USectorLocationInterface>())
	{
		GetOwner<ISectorLocationInterface>()->GetSectorLocation()->SetSector(Sector);
	}
}
