// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityButtonList.h"
#include "CommonListView.h"
#include "Log.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/GameUI/StructurePartClass.h"

void UStructureAbilityButtonList::UpdateButtons(AStructure* InStructure) const
{
	TArray<TSubclassOf<AStructurePart>> PartClasses;
	for(const AStructurePart* Part : InStructure->GetParts())
	{
		if(!PartClasses.Contains(Part->GetClass()))
		{
			PartClasses.Add(Part->GetClass());
		}
	}

	UE_LOG(LogDarkFrontier, Log, TEXT("Updating structure ability buttons with %d unique part types"), PartClasses.Num());

	PartList->ClearListItems();
	for(const TSubclassOf<AStructurePart> PartClass : PartClasses)
	{
		UStructurePartClass* ClassObj = NewObject<UStructurePartClass>();
		ClassObj->TargetStructure = InStructure;
		ClassObj->PartClass = PartClass;
		PartList->AddItem(ClassObj);
	}
	PartList->RegenerateAllEntries();
}
