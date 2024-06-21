// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureSlotOption.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Screens/StructureDetails/StructureSlotOptionObject.h"

void UStructureSlotOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UStructureSlotOptionObject* Object = Cast<UStructureSlotOptionObject>(ListItemObject);
	SlotName = Object->SlotName;

	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructureSlotOption>(this, &UStructureSlotOption::OnOptionClicked);
	NameText->SetText(SlotName);
}

void UStructureSlotOption::OnOptionClicked() const
{
	const UWidget* Widget = GetOwningListView();
	if(!Widget)
	{
		Widget = this;
	}

	UStructureDetails* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
	Screen->AttachWithSlotName(SlotName);
}
