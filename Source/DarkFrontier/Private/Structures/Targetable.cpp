// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Targetable.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Structure.h"

bool UTargetable::IsTargetable(AStructure* Structure) const
{
	GUARD_RETURN(GetOwner()->Implements<USectorLocationInterface>(), false);
	
	const ASector* Sector = GetOwner<ISectorLocationInterface>()->GetSectorLocation()->GetSector();
	GUARD_RETURN(Sector == Structure->GetSectorLocation()->GetSector(), false);

	// TODO check detection and detectability
	
	return true;
}

TSubclassOf<USelector> UTargetable::GetSelectorClass() const
{
	return SelectorClass;
}
