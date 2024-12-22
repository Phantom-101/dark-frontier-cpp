// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/ListSelectionModal.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "UI/Widgets/ListSelectionOptionParams.h"

void UListSelectionModal::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UListSelectionModal>(this, &UListSelectionModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UListSelectionModal>(this, &UListSelectionModal::HandleCancel);
}

void UListSelectionModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UListSelectionModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UListSelectionModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UListSelectionModal::SetOptions(const TArray<UObject*>& InOptions)
{
	Options = InOptions;
	SetCurrentOption(nullptr);
}

void UListSelectionModal::SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial)
{
	SetOptions(InOptions);
	SetCurrentOption(Initial);
}

void UListSelectionModal::SetCurrentOption(UObject* Option)
{
	if(Option == nullptr || Options.Contains(Option))
	{
		CurrentOption = Option;
	}

	ConfirmButton->SetIsEnabled(Options.Contains(CurrentOption));
}

void UListSelectionModal::SetBuilder(const TFunction<UWidget*(UObject*)>& Builder)
{
	OptionBuilder = Builder;
	Rebuild();
}

UObject* UListSelectionModal::GetCurrentOption()
{
	return CurrentOption;
}

void UListSelectionModal::Rebuild()
{
	SelectionList->ClearListItems();
	for(UObject* Option : Options)
	{
		UListSelectionOptionParams* Params = NewObject<UListSelectionOptionParams>();
		Params->OwningModal = this;
		Params->Option = Option;
		Params->Builder = OptionBuilder;
		SelectionList->AddItem(Params);
	}
	SelectionList->RegenerateAllEntries();
}

void UListSelectionModal::HandleConfirm()
{
	if(Options.Contains(CurrentOption))
	{
		DeactivateWidget();
		OnConfirmed.Broadcast(CurrentOption);
	}
}

void UListSelectionModal::HandleCancel()
{
	DeactivateWidget();
	OnCanceled.Broadcast();
}
