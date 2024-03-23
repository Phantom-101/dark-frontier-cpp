// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureCard.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/Structure.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Widgets/ClickableCard.h"

void UStructureCard::NativeConstruct()
{
	Super::NativeConstruct();

	CardButton->OnClicked.Unbind();
	CardButton->OnClicked.BindUObject<UStructureCard>(this, &UStructureCard::OnCardClicked);
}

void UStructureCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<AStructure>(ListItemObject));
}

void UStructureCard::SetTarget(AStructure* InTargetStructure)
{
	TargetStructure = InTargetStructure;

	if(TargetStructure == nullptr)
	{
		NameText->SetText(FText::FromString("None"));
	}
	else
	{
		NameText->SetText(FText::FromString(TargetStructure->GetName()));
	}
}

void UStructureCard::OnCardClicked() const
{
	if(TargetStructure != nullptr)
	{
		const UWidget* Widget = GetOwningListView();
		if(Widget == nullptr)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->Select(TargetStructure);
	}
}
