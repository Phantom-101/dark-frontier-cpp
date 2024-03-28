// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/Structure.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructureCard::NativeConstruct()
{
	Super::NativeConstruct();
	
	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructureCard>(this, &UStructureCard::OnCardClicked);
}

void UStructureCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<AStructure>(ListItemObject));
}

void UStructureCard::SetTarget(AStructure* InTargetStructure)
{
	TargetStructure = InTargetStructure;

	if(IsValid(TargetStructure))
	{
		NameText->SetText(FText::FromString(TargetStructure->GetName()));
	}
	else
	{
		NameText->SetText(FText::FromString("None"));
	}
}

void UStructureCard::OnCardClicked() const
{
	if(IsValid(TargetStructure))
	{
		const UWidget* Widget = GetOwningListView();
		if(!Widget)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->Select(TargetStructure);
	}
}
