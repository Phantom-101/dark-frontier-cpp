// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Indicators/StructureIndicatorMapping.h"
#include "Structures/Indications/StructureIndication.h"

TSubclassOf<UStructureIndicator> UStructureIndicatorMapping::Map(const TSubclassOf<UStructureIndication>& IndicationClass) const
{
	for (UClass* Class = IndicationClass; Class->IsChildOf<UStructureIndication>(); Class = Class->GetSuperClass())
	{
		TSubclassOf<UStructureIndication> Subclass = TSubclassOf<UStructureIndication>(Class);
		if(Mapping.Contains(Subclass))
		{
			return Mapping.FindRef(Subclass);
		}
	}

	return nullptr;
}
