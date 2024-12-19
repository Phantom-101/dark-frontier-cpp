// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Controls/StructurePartControlsMapping.h"
#include "Structures/StructurePart.h"

TSubclassOf<UStructurePartControls> UStructurePartControlsMapping::Map(const TSubclassOf<AStructurePart>& PartClass) const
{
	for (UClass* Class = PartClass; Class->IsChildOf<AStructurePart>(); Class = Class->GetSuperClass())
	{
		TSubclassOf<AStructurePart> Subclass = TSubclassOf<AStructurePart>(Class);
		if(Mapping.Contains(Subclass))
		{
			return Mapping.FindRef(Subclass);
		}
	}

	return nullptr;
}
