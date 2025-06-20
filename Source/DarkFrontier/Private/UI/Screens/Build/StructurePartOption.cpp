// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Build/StructurePartOption.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/Build/BuildScreen.h"
#include "UI/Screens/Build/StructurePartOptionObject.h"

void UStructurePartOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UStructurePartOptionObject* Object = Cast<UStructurePartOptionObject>(ListItemObject);
	PartClass = Object->PartClass;
	
	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructurePartOption>(this, &UStructurePartOption::OnOptionClicked);
	TypeText->SetText(PartClass->GetDefaultObject<AStructurePart>()->GetTypeName());
}

void UStructurePartOption::OnOptionClicked() const
{
	UBuildScreen* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UBuildScreen>(this);
	Screen->SetPartType(PartClass);
}
