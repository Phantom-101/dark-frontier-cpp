// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotOption.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Screens/StructureDetails/StructurePartSlotOptionObject.h"

void UStructurePartSlotOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UStructurePartSlotOptionObject* Object = Cast<UStructurePartSlotOptionObject>(ListItemObject);
	SlotName = Object->SlotName;

	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructurePartSlotOption>(this, &UStructurePartSlotOption::OnOptionClicked);
	NameText->SetText(SlotName);
}

void UStructurePartSlotOption::OnOptionClicked() const
{
	const UWidget* Widget = GetOwningListView();
	if(!Widget)
	{
		Widget = this;
	}

	UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
	Screen->Edit(SlotName);
}
