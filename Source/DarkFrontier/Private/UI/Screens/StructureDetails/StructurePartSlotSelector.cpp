// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotSelector.h"
#include "CommonListView.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructurePartSlotOptionObject.h"

void UStructurePartSlotSelector::PopulateOptions(const TSubclassOf<AStructurePart> InClass, const UStructurePartSlot* InSlot) const
{
	OptionList->ClearListItems();
	for(const UStructurePartSlot* Option : AStructurePart::GetCompatiblePartSlots_CDO(InClass, InSlot))
	{
		UStructurePartSlotOptionObject* Object = NewObject<UStructurePartSlotOptionObject>();
		Object->Init(Option->SlotName);
		OptionList->AddItem(Object);
	}
}
