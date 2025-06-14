// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureCard.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "UI/Screens/BuildUI/BuildUI.h"

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
		UBuildUI* Screen = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UBuildUI>(this);
		Screen->SelectStructure();
	}
}
