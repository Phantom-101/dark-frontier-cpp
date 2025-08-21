// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Refit/RefitPartList.h"
#include "CommonListView.h"
#include "Structures/StructurePart.h"

void URefitPartList::Populate(TArray<TSubclassOf<AStructurePart>> Parts) const
{
	ListView->ClearListItems();
	for(TSubclassOf Part : Parts)
	{
		if(Part->GetDefaultObject<AStructurePart>()->HasMatchingGameplayTag(Tag))
		{
			ListView->AddItem(Part);
		}
	}
}
