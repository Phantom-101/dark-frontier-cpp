// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructurePartCardList.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/StructurePart.h"

void UStructurePartCardList::SetHeader(const FText& InHeader) const
{
	HeaderText->SetText(InHeader);
}

void UStructurePartCardList::SetHeaderColor(const FLinearColor& InColor) const
{
	HeaderText->SetColorAndOpacity(InColor);
}

void UStructurePartCardList::SetParts(const TArray<AStructurePart*>& InParts) const
{
	PartList->ClearListItems();
	for(AStructurePart* Part : InParts)
	{
		PartList->AddItem(Part);
	}
	PartList->RegenerateAllEntries();
}
