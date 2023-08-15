// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleSectionSlotEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleSectionSlotEntryObject.h"

void UCompatibleSectionSlotEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleSectionSlotEntryObject* Obj = Cast<UCompatibleSectionSlotEntryObject>(ListItemObject);
	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());
	
	NameText->SetText(Obj->SlotName);
	AddButton->OnClicked().AddUObject<UCompatibleSectionSlotEntry>(this, &UCompatibleSectionSlotEntry::OnAddButtonClicked);
}

void UCompatibleSectionSlotEntry::OnAddButtonClicked() const
{
	const UCompatibleSectionSlotEntryObject* Obj = GetListItem<UCompatibleSectionSlotEntryObject>();
	StructureBuilder->AttachSectionType(Obj->SectionType, Obj->SlotName);
}
