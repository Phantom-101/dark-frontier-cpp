// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
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

	if(IsValid(TargetPart))
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
	else
	{
		TypeText->SetText(FText::FromString("None"));
	}
}

void UStructurePartCard::OnCardClicked() const
{
	if(IsValid(TargetPart))
	{
		const UWidget* Widget = GetOwningListView();
		if(!Widget)
		{
			Widget = this;
		}

		UStructureDetails* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureDetails>(Widget);
		Screen->SelectPart(TargetPart);
	}
}

void UStructurePartCard::OnRemoveButtonClicked() const
{
	TargetPart->DetachSlots();
}

void UStructurePartCard::OnLookButtonClicked() const
{
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		Controller->SetCameraTargetActor(TargetPart);
	}
}
