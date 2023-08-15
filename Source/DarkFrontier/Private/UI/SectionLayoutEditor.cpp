// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SectionLayoutEditor.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/StructureSection.h"
#include "Structures/Structure.h"
#include "Structures/StructureEquipmentSlot.h"
#include "Structures/StructureSectionSlot.h"

void USectionLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	const AStructureSection* Section = Cast<AStructureSection>(ListItemObject);

	TypeText->SetText(Section->GetClass()->GetDisplayNameText());
	IdText->SetText(FText::FromString(FString::Printf(TEXT("#%i"), Section->SectionId)));
	RootSectionText->SetVisibility(Section == Section->OwningStructure->GetRootSection() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	SectionSlotList->ClearListItems();
	for(UStructureSectionSlot* SectionSlot : Section->SectionSlots)
	{
		SectionSlotList->AddItem(SectionSlot);
	}
	SectionSlotList->RegenerateAllEntries();

	EquipmentSlotList->ClearListItems();
	for(UStructureEquipmentSlot* EquipmentSlot : Section->EquipmentSlots)
	{
		EquipmentSlotList->AddItem(EquipmentSlot);
	}
	EquipmentSlotList->RegenerateAllEntries();
}
