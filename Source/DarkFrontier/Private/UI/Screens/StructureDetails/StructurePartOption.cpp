// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartOption.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Screens/StructureDetails/StructurePartOptionObject.h"
#include "UI/Widgets/ClickableCard.h"

void UStructurePartOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UStructurePartOptionObject* Object = Cast<UStructurePartOptionObject>(ListItemObject);
	PartClass = Object->PartClass;
	
	CardButton->OnClicked.Unbind();
	CardButton->OnClicked.BindUObject<UStructurePartOption>(this, &UStructurePartOption::OnOptionClicked);
	TypeText->SetText(PartClass->GetDefaultObject<AStructurePart>()->TypeName);
}

void UStructurePartOption::OnOptionClicked() const
{
	const UWidget* Widget = GetOwningListView();
	if(Widget == nullptr)
	{
		Widget = this;
	}

	UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
	Screen->Edit(PartClass);
}
