// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Build/StructureSlotOption.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIFunctionLibrary.h"
#include "UI/Screens/Build/BuildScreen.h"
#include "UI/Screens/Build/StructureSlotOptionObject.h"

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
	UBuildScreen* Screen = UUIFunctionLibrary::GetParentWidgetOfClass<UBuildScreen>(this);
	Screen->AttachWithSlotName(SlotName);
}
