// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureSlotCardList.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/StructureSlot.h"

void UStructureSlotCardList::Init(TArray<UStructureSlot*> InSlots, const FText& InHeader, const FLinearColor InColor) const
{
	NameText->SetText(InHeader);
	NameText->SetColorAndOpacity(InColor);

	SlotList->ClearListItems();
	for(UStructureSlot* PartSlot : InSlots)
	{
		SlotList->AddItem(PartSlot);
	}
	SlotList->RegenerateAllEntries();
	// We don't need to scroll the first item into view as all elements are of fixed height
}
