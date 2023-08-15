// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleSectionEntry.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleSectionEntryObject.h"
#include "UI/CompatibleSectionSlotEntryObject.h"

void UCompatibleSectionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleSectionEntryObject* Obj = Cast<UCompatibleSectionEntryObject>(ListItemObject);
	UStructureBuilder* StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	TypeText->SetText(Obj->SectionType->GetDisplayNameText());
	SlotList->ClearListItems();
	AStructureSection* Section = Cast<AStructureSection>(GetWorld()->SpawnActor(Obj->SectionType));
	for(const UStructureSectionSlot* SectionSlot : Section->GetCompatibleSectionSlots(StructureBuilder->GetSelectedSectionSlot()->SlotType))
	{
		UCompatibleSectionSlotEntryObject* SubObj = NewObject<UCompatibleSectionSlotEntryObject>();
		SubObj->Init(SectionSlot);
		SlotList->AddItem(SubObj);
	}
	Section->Destroy();
	SlotList->RegenerateAllEntries();
}
