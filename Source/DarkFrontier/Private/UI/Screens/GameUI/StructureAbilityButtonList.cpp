// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityButtonList.h"
#include "CommonListView.h"
#include "Log.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureAbilityProxyGroup.h"

void UStructureAbilityButtonList::UpdateButtons(AStructure* InStructure) const
{
	TArray<UStructureAbilityProxyGroup*> ProxyGroups = InStructure->GetAbilityProxyGroups();

	UE_LOG(LogDarkFrontier, Log, TEXT("Updating structure ability buttons with %d ability proxy groups"), ProxyGroups.Num());

	PartList->ClearListItems();
	for(UStructureAbilityProxyGroup* ProxyGroup : ProxyGroups)
	{
		PartList->AddItem(ProxyGroup);
	}
	PartList->RegenerateAllEntries();
}
