// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureSlotOption.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/BuildUI/BuildUI.h"
#include "UI/Screens/BuildUI/StructureSlotOptionObject.h"

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

	UBuildUI* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UBuildUI>(Widget);
	Screen->AttachWithSlotName(SlotName);
}
