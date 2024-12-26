// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Modals/ListBoxModal.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "UI/Widgets/Interaction/ListBox.h"

void UListBoxModal::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked().Clear();
	ConfirmButton->OnClicked().AddUObject<UListBoxModal>(this, &UListBoxModal::HandleConfirm);
	CancelButton->OnClicked().Clear();
	CancelButton->OnClicked().AddUObject<UListBoxModal>(this, &UListBoxModal::HandleCancel);
}

void UListBoxModal::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UListBoxModal::NativeGetDesiredFocusTarget() const
{
	return CancelButton;
}

bool UListBoxModal::NativeOnHandleBackAction()
{
	HandleCancel();
	return true;
}

void UListBoxModal::SetOptions(const TArray<UObject*>& InOptions) const
{
	ListBox->SetOptions(InOptions);
}

void UListBoxModal::SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial) const
{
	ListBox->SetOptionsWithInitial(InOptions, Initial);
}

void UListBoxModal::SetCurrentOption(UObject* Option) const
{
	ListBox->SetCurrentOption(Option);

	ConfirmButton->SetIsEnabled(ListBox->IsCurrentOptionValid()); // TODO listen to listbox current option change event
}

void UListBoxModal::SetBuilder(const TFunction<UWidget*(UObject*)>& Builder) const
{
	ListBox->SetBuilder(Builder);
}

bool UListBoxModal::IsCurrentOptionValid() const
{
	return ListBox->IsCurrentOptionValid();
}

UObject* UListBoxModal::GetCurrentOption() const
{
	return ListBox->GetCurrentOption();
}

void UListBoxModal::HandleConfirm()
{
	if(ListBox->IsCurrentOptionValid())
	{
		DeactivateWidget();
		OnConfirmed.Broadcast(ListBox->GetCurrentOption());
	}
}

void UListBoxModal::HandleCancel()
{
	DeactivateWidget();
	OnCanceled.Broadcast();
}
