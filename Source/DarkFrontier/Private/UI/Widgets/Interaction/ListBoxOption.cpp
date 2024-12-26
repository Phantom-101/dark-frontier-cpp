// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/ListBoxOption.h"
#include "CommonButtonBase.h"
#include "Components/NamedSlot.h"
#include "UI/Widgets/Interaction/ListBox.h"
#include "UI/Widgets/Visuals/ListBoxOptionParams.h"

void UListBoxOption::NativeConstruct()
{
	Super::NativeConstruct();

	SelectButton->SetIsSelectable(true);
	SelectButton->OnClicked().Clear();
	SelectButton->OnClicked().AddUObject<UListBoxOption>(this, &UListBoxOption::HandleSelect);
}

void UListBoxOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	Params = Cast<UListBoxOptionParams>(ListItemObject);

	ContentSlot->ClearChildren();
	ContentSlot->AddChild(Params->Builder(Params->Option));
}

void UListBoxOption::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SelectButton->SetIsSelected(IsValid(Params) && Params->ListBox->GetCurrentOption() == Params->Option);
}

void UListBoxOption::HandleSelect() const
{
	if(IsValid(Params))
	{
		Params->ListBox->SetCurrentOption(Params->Option);
	}
}
