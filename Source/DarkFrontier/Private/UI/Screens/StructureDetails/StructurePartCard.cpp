// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"

void UStructurePartCard::NativeConstruct()
{
	Super::NativeConstruct();
	
	CardButton->OnClicked().Clear();
	CardButton->OnClicked().AddUObject<UStructurePartCard>(this, &UStructurePartCard::OnCardClicked);

	RemoveButton->OnClicked().Clear();
	RemoveButton->OnClicked().AddUObject<UStructurePartCard>(this, &UStructurePartCard::OnRemoveButtonClicked);
	
	LookButton->OnClicked().Clear();
	LookButton->OnClicked().AddUObject<UStructurePartCard>(this, &UStructurePartCard::OnLookButtonClicked);
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
		TypeText->SetText(TargetPart->GetTypeName());
		if(TargetPart->IsRootPart())
		{
			RemoveButton->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			RemoveButton->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
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

void UStructurePartCard::OnRemoveButtonClicked() const
{
	TargetPart->DetachSlots();
}

void UStructurePartCard::OnLookButtonClicked() const
{
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(Controller != nullptr)
	{
		Controller->SetCameraTargetActor(TargetPart);
	}
}
