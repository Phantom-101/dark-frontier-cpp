// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotListView.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePartSlotType.h"

void UStructurePartSlotListView::Init(AStructure* InTarget, const UStructurePartSlotType* InType) const
{
	if(InType == nullptr)
	{
		NameText->SetText(FText::FromString("Miscellaneous"));
		NameText->SetColorAndOpacity(FLinearColor::White);
	}
	else
	{
		NameText->SetText(InType->TypeName);
		NameText->SetColorAndOpacity(InType->Color);
	}

	SlotList->ClearListItems();
	for(AStructurePart* Part : InTarget->GetParts())
	{
		for(UStructurePartSlot* PartSlot : Part->GetSlots())
		{
			if(PartSlot->GetSlotType() == InType)
			{
				SlotList->AddItem(PartSlot);
			}
		}
	}
	SlotList->RegenerateAllEntries();
	SlotList->ScrollIndexIntoView(0);
}
