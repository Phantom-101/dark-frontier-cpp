// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructurePartAbilityButtonList.h"
#include "CommonListView.h"
#include "Structures/StructureGameplayAbility.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/GameUI/StructurePartAbilityClass.h"
#include "UI/Screens/GameUI/StructurePartClass.h"

void UStructurePartAbilityButtonList::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	ClassObj = Cast<UStructurePartClass>(ListItemObject);

	ButtonList->ClearListItems();
	for(const TSubclassOf<UStructureGameplayAbility> AbilityClass : ClassObj->PartClass->GetDefaultObject<AStructurePart>()->GetAbilities())
	{
		UStructurePartAbilityClass* AbilityClassObj = NewObject<UStructurePartAbilityClass>();
		AbilityClassObj->TargetStructure = ClassObj->TargetStructure;
		AbilityClassObj->PartClass = ClassObj->PartClass;
		AbilityClassObj->AbilityClass = AbilityClass;
		ButtonList->AddItem(AbilityClassObj);
	}
	ButtonList->RegenerateAllEntries();
}
