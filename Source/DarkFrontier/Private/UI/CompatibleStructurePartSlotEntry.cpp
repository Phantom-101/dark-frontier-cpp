// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartSlotEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleStructurePartSlotEntryObject.h"

void UCompatibleStructurePartSlotEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleStructurePartSlotEntryObject* Obj = Cast<UCompatibleStructurePartSlotEntryObject>(ListItemObject);
	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());
	
	NameText->SetText(Obj->SlotName);
	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UCompatibleStructurePartSlotEntry>(this, &UCompatibleStructurePartSlotEntry::OnAddButtonClicked);
}

void UCompatibleStructurePartSlotEntry::OnAddButtonClicked() const
{
	const UCompatibleStructurePartSlotEntryObject* Obj = GetListItem<UCompatibleStructurePartSlotEntryObject>();
	StructureBuilder->AttachPartOfType(Obj->PartClass, Obj->SlotName);
}
