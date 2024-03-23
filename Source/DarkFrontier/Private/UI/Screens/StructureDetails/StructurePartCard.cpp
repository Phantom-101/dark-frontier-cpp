// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartCard.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Widgets/ClickableCard.h"

void UStructurePartCard::NativeConstruct()
{
	Super::NativeConstruct();
	
	CardButton->OnClicked.Unbind();
	CardButton->OnClicked.BindUObject<UStructurePartCard>(this, &UStructurePartCard::OnCardClicked);
}

void UStructurePartCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<AStructurePart>(ListItemObject));
}

void UStructurePartCard::SetTarget(AStructurePart* InTargetPart)
{
	TargetPart = InTargetPart;

	if(TargetPart == nullptr)
	{
		TypeText->SetText(FText::FromString("None"));
	}
	else
	{
		TypeText->SetText(TargetPart->TypeName);
	}
}

void UStructurePartCard::OnCardClicked() const
{
	if(TargetPart != nullptr)
	{
		const UWidget* Widget = GetOwningListView();
		if(Widget == nullptr)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->Select(TargetPart);
	}
}
