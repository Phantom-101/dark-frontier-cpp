// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructurePartSlotCard::NativeConstruct()
{
	Super::NativeConstruct();

	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnCardClicked);

	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnAddButtonClicked);

	DetachButton->OnClicked().Clear();
	DetachButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnDetachButtonClicked);
	
	LookButton->OnClicked().Clear();
	LookButton->OnClicked().AddUObject<UStructurePartSlotCard>(this, &UStructurePartSlotCard::OnLookButtonClicked);
}

void UStructurePartSlotCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<UStructurePartSlot>(ListItemObject));
}

void UStructurePartSlotCard::SetTarget(UStructurePartSlot* InTargetSlot)
{
	TargetSlot = InTargetSlot;

	if(IsValid(TargetSlot))
	{
		TypeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameText->SetText(FText::FromString(FString::Printf(TEXT("(%s)"), *TargetSlot->GetSlotName().ToString())));
		if(IsValid(InTargetSlot->GetAttachedSlot()))
		{
			TypeText->SetText(InTargetSlot->GetAttachedSlot()->GetOwningPart()->GetTypeName());
		}
		else
		{
			TypeText->SetText(FText::FromString("None"));
		}
	}
	else
	{
		TypeText->SetVisibility(ESlateVisibility::Collapsed);
		NameText->SetText(FText::FromString("(None)"));
	}
}

void UStructurePartSlotCard::OnCardClicked() const
{
	if(IsValid(TargetSlot) && IsValid(TargetSlot->GetOwningPart()))
	{
		const UWidget* Widget = GetOwningListView();
		if(!Widget)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->Select(TargetSlot->GetOwningPart());
	}
}

void UStructurePartSlotCard::OnAddButtonClicked() const
{
	if(IsValid(TargetSlot))
	{
		if(!TargetSlot->GetAttachedSlot())
		{
			const UWidget* Widget = GetOwningListView();
			if(!Widget)
			{
				Widget = this;
			}

			UStructureDetails* Screen = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
			Screen->Edit(TargetSlot);
		}
	}
}

void UStructurePartSlotCard::OnDetachButtonClicked() const
{
	TargetSlot->TryDetach();
}

void UStructurePartSlotCard::OnLookButtonClicked() const
{
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		Controller->SetCameraTargetComponent(TargetSlot);
	}
}
