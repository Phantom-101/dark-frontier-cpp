// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureSlotSelector.h"
#include "CommonListView.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/BuildUI/BuildUI.h"
#include "UI/Screens/BuildUI/StructureSlotOptionObject.h"

void UStructureSlotSelector::PopulateOptions(const TSubclassOf<AStructurePart> InClass, const UStructureSlot* InSlot) const
{
	OptionList->ClearListItems();
	TArray<const UStructureSlot*> Options = AStructurePart::GetCompatibleSlots_CDO(InClass, InSlot);
	if(Options.Num() == 1)
	{
		UBuildUI* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UBuildUI>(this);
		Screen->AttachWithSlotName(Options[0]->GetSlotName());
	}
	else
	{
		for(const UStructureSlot* Option : Options)
		{
			UStructureSlotOptionObject* Object = NewObject<UStructureSlotOptionObject>();
			Object->SlotName = Option->GetSlotName();
			OptionList->AddItem(Object);
		}
	}
}
