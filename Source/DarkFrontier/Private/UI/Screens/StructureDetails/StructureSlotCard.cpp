// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureSlotCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Objects/ComponentViewTarget.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructureSlotCard::NativeConstruct()
{
	Super::NativeConstruct();

	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructureSlotCard>(this, &UStructureSlotCard::OnCardClicked);

	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UStructureSlotCard>(this, &UStructureSlotCard::OnAddButtonClicked);

	DetachButton->OnClicked().Clear();
	DetachButton->OnClicked().AddUObject<UStructureSlotCard>(this, &UStructureSlotCard::OnDetachButtonClicked);
	
	LookButton->OnClicked().Clear();
	LookButton->OnClicked().AddUObject<UStructureSlotCard>(this, &UStructureSlotCard::OnLookButtonClicked);
}

void UStructureSlotCard::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetTarget(Cast<UStructureSlot>(ListItemObject));
}

void UStructureSlotCard::SetTarget(UStructureSlot* InTargetSlot)
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

void UStructureSlotCard::OnCardClicked() const
{
	if(IsValid(TargetSlot) && IsValid(TargetSlot->GetAttachedSlot()))
	{
		const UWidget* Widget = GetOwningListView();
		if(!Widget)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->SelectPart(TargetSlot->GetAttachedSlot()->GetOwningPart());
	}
}

void UStructureSlotCard::OnAddButtonClicked() const
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

			UStructureDetails* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
			Screen->SetBaseSlot(TargetSlot);
		}
	}
}

void UStructureSlotCard::OnDetachButtonClicked() const
{
	TargetSlot->TryDetach();
}

void UStructureSlotCard::OnLookButtonClicked() const
{
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		UComponentViewTarget* ViewTarget = NewObject<UComponentViewTarget>();
		ViewTarget->Component = TargetSlot;
		Controller->SetViewTarget(ViewTarget);
	}
}
