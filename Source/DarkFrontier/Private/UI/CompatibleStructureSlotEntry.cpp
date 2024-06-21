// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructureSlotEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/CompatibleStructureSlotEntryObject.h"

void UCompatibleStructureSlotEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UCompatibleStructureSlotEntryObject* Obj = Cast<UCompatibleStructureSlotEntryObject>(ListItemObject);
	StructureBuilder = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());
	
	NameText->SetText(Obj->SlotName);
	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UCompatibleStructureSlotEntry>(this, &UCompatibleStructureSlotEntry::OnAddButtonClicked);
}

void UCompatibleStructureSlotEntry::OnAddButtonClicked() const
{
	const UCompatibleStructureSlotEntryObject* Obj = GetListItem<UCompatibleStructureSlotEntryObject>();
	StructureBuilder->AttachPart(Obj->PartClass, Obj->SlotName);
}
