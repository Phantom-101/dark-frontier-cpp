// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/ListSelectionOption.h"
#include "CommonButtonBase.h"
#include "Components/NamedSlot.h"
#include "UI/Widgets/ListSelectionModal.h"
#include "UI/Widgets/ListSelectionOptionParams.h"

void UListSelectionOption::NativeConstruct()
{
	Super::NativeConstruct();

	SelectButton->SetIsSelectable(true);
	SelectButton->OnClicked().Clear();
	SelectButton->OnClicked().AddUObject<UListSelectionOption>(this, &UListSelectionOption::HandleSelect);
}

void UListSelectionOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UListSelectionOptionParams* Params = Cast<UListSelectionOptionParams>(ListItemObject);

	OwningModal = Params->OwningModal;
	Option = Params->Option;

	ContentSlot->ClearChildren();
	ContentSlot->AddChild(Params->Builder(Params->Option));
}

void UListSelectionOption::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SelectButton->SetIsSelected(IsValid(OwningModal) && OwningModal->GetCurrentOption() == Option);
}

void UListSelectionOption::HandleSelect() const
{
	if(IsValid(OwningModal))
	{
		OwningModal->SetCurrentOption(Option);
	}
}
