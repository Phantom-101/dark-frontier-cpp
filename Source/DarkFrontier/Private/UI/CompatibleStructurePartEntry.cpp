// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartEntry.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/CompatibleStructurePartEntryObject.h"
#include "UI/CompatibleStructureSlotEntryObject.h"

void UCompatibleStructurePartEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleStructurePartEntryObject* Obj = Cast<UCompatibleStructurePartEntryObject>(ListItemObject);
	const UStructureBuilder* StructureBuilder = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	TypeText->SetText(Obj->PartName);
	SlotList->ClearListItems();
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(Obj->PartClass));
	for(const UStructureSlot* SectionSlot : Section->GetCompatibleSlots(StructureBuilder->GetSelectedSlot()))
	{
		UCompatibleStructureSlotEntryObject* SubObj = NewObject<UCompatibleStructureSlotEntryObject>();
		SubObj->Init(SectionSlot);
		SlotList->AddItem(SubObj);
	}
	Section->Destroy();
	SlotList->RegenerateAllEntries();
	SlotList->ScrollIndexIntoView(0);
}
