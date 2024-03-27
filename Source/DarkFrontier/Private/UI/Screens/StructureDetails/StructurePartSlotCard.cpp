// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructurePartSlotCard::NativeConstruct()
{
	Super::NativeConstruct();

	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnAddButtonClicked);
}

void UStructurePartSlotCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<UStructurePartSlot>(ListItemObject));
}

void UStructurePartSlotCard::SetTarget(UStructurePartSlot* InTargetSlot)
{
	TargetSlot = InTargetSlot;

	if(TargetSlot == nullptr)
	{
		TypeText->SetVisibility(ESlateVisibility::Collapsed);
		NameText->SetText(FText::FromString("(None)"));
	}
	else
	{
		TypeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameText->SetText(FText::FromString(FString::Printf(TEXT("(%s)"), *TargetSlot->GetSlotName().ToString())));
		if(InTargetSlot->GetAttachedSlot() == nullptr)
		{
			TypeText->SetText(FText::FromString("None"));
		}
		else
		{
			TypeText->SetText(InTargetSlot->GetAttachedSlot()->GetOwningPart()->GetTypeName());
		}
	}
}

void UStructurePartSlotCard::OnAddButtonClicked() const
{
	if(TargetSlot != nullptr)
	{
		if(TargetSlot->GetAttachedSlot() == nullptr)
		{
			const UWidget* Widget = GetOwningListView();
			if(Widget == nullptr)
			{
				Widget = this;
			}

			UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
			Screen->Edit(TargetSlot);
		}
	}
}
