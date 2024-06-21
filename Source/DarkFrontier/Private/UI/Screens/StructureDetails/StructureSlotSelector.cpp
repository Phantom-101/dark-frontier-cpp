// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureSlotSelector.h"
#include "CommonListView.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/StructureDetails/StructureSlotOptionObject.h"

void UStructureSlotSelector::PopulateOptions(const TSubclassOf<AStructurePart> InClass, const UStructureSlot* InSlot) const
{
	OptionList->ClearListItems();
	for(const UStructureSlot* Option : AStructurePart::GetCompatibleSlots_CDO(InClass, InSlot))
	{
		UStructureSlotOptionObject* Object = NewObject<UStructureSlotOptionObject>();
		Object->SlotName = Option->GetSlotName();
		OptionList->AddItem(Object);
	}
}
