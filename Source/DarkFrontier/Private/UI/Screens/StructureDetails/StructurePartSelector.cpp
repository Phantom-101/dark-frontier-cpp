// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSelector.h"
#include "CommonListView.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructurePartOptionObject.h"

void UStructurePartSelector::PopulateOptions(TArray<TSubclassOf<AStructurePart>> InOptions, const UStructurePartSlot* InSlot) const
{
	OptionList->ClearListItems();
	for(const TSubclassOf<AStructurePart> Option : InOptions)
	{
		if(AStructurePart::GetCompatibleSlots_CDO(Option, InSlot).Num() > 0)
		{
			UStructurePartOptionObject* Object = NewObject<UStructurePartOptionObject>();
			Object->Init(Option);
			OptionList->AddItem(Object);
		}
	}
}
