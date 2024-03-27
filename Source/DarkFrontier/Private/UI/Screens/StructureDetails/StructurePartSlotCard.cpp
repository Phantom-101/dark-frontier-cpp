// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructurePartSlotCard::NativeConstruct()
{
	Super::NativeConstruct();

	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnCardClicked);
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
		NameText->SetText(FText::FromString("None"));
	}
	else
	{
		NameText->SetText(TargetSlot->GetSlotName());
	}
}

void UStructurePartSlotCard::OnCardClicked() const
{
	if(TargetSlot != nullptr)
	{
		const UWidget* Widget = GetOwningListView();
		if(Widget == nullptr)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->Select(TargetSlot);
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
