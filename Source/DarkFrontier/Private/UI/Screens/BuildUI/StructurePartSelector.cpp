// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructurePartSelector.h"
#include "CommonListView.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/BuildUI/StructurePartOptionObject.h"

void UStructurePartSelector::PopulateOptions(TArray<TSubclassOf<AStructurePart>> InOptions, const UStructureSlot* InSlot) const
{
	OptionList->ClearListItems();
	for(const TSubclassOf<AStructurePart> Option : InOptions)
	{
		if(AStructurePart::GetCompatibleSlots_CDO(Option, InSlot).Num() > 0)
		{
			UStructurePartOptionObject* Object = NewObject<UStructurePartOptionObject>();
			Object->PartClass = Option;
			OptionList->AddItem(Object);
		}
	}
}
