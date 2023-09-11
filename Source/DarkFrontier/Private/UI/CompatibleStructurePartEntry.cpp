// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartEntry.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleStructurePartEntryObject.h"
#include "UI/CompatibleStructurePartSlotEntryObject.h"

void UCompatibleStructurePartEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleStructurePartEntryObject* Obj = Cast<UCompatibleStructurePartEntryObject>(ListItemObject);
	const UStructureBuilder* StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	TypeText->SetText(Obj->PartClass->GetDisplayNameText());
	SlotList->ClearListItems();
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(Obj->PartClass));
	for(const UStructurePartSlot* SectionSlot : Section->GetCompatiblePartSlots(StructureBuilder->GetSelectedPartSlot()->SlotType))
	{
		UCompatibleStructurePartSlotEntryObject* SubObj = NewObject<UCompatibleStructurePartSlotEntryObject>();
		SubObj->Init(SectionSlot);
		SlotList->AddItem(SubObj);
	}
	Section->Destroy();
	SlotList->RegenerateAllEntries();
}
