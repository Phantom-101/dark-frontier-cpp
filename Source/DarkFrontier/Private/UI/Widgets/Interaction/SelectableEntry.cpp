// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "CommonButtonBase.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "UI/Widgets/Interaction/Stripe.h"

void USelectableEntry::NativeConstruct()
{
	Super::NativeConstruct();

	// Setting interaction enabled will not update button style immediately
	// It will switch to disabled style upon leaving and reentering the tab
	SelectButton->SetIsEnabled(false);
	// Setting enabled or interaction enabled will not automatically change focusable
	SelectButton->SetIsFocusable(false);
	if(Stripe != nullptr)
	{
		Stripe->SetIsVisible(false);
	}
	
	SelectButton->OnClicked().AddUObject(this, &USelectableEntry::HandleClick);
}

void USelectableEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectButton->SetIsEnabled(true);
	SelectButton->SetIsFocusable(true);
	if(Stripe != nullptr)
	{
		Stripe->SetIsVisible(IsListItemSelected());
	}

	ListView = Cast<UListView>(GetOwningListView());
	GUARD(ensure(IsValid(ListView)));
	OnSelectionChangedHandle = ListView->OnItemSelectionChanged().AddUObject(this, &USelectableEntry::UpdateStripe);
}

void USelectableEntry::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	SelectButton->SetIsEnabled(false);
	SelectButton->SetIsFocusable(false);
	if(Stripe != nullptr)
	{
		Stripe->SetIsVisible(false);
	}

	GUARD(ensure(IsValid(ListView)));
	ListView->OnItemSelectionChanged().Remove(OnSelectionChangedHandle);
	ListView = nullptr;
	OnSelectionChangedHandle = FDelegateHandle();
}

void USelectableEntry::HandleClick() const
{
	GUARD(ListView != nullptr);
	switch(ListView->GetSelectionMode())
	{
		case ESelectionMode::Single:
			// Deselect old item before selecting new item as single mode will block having two selected items at once
			ListView->SetItemSelection(ListView->GetSelectedItem(), false, ESelectInfo::OnMouseClick);
			ListView->SetItemSelection(GetListItem(), true, ESelectInfo::OnMouseClick);
			break;
		case ESelectionMode::SingleToggle:
			if(IsListItemSelected())
			{
				ListView->SetItemSelection(GetListItem(), false, ESelectInfo::OnMouseClick);
			}
			else
			{
				// Same as single selection
				ListView->SetItemSelection(ListView->GetSelectedItem(), false, ESelectInfo::OnMouseClick);
				ListView->SetItemSelection(GetListItem(), true, ESelectInfo::OnMouseClick);
			}
			break;
		case ESelectionMode::Multi:
			ListView->SetItemSelection(GetListItem(), !IsListItemSelected(), ESelectInfo::OnMouseClick);
			break;
		default:
			break;
	}
}

void USelectableEntry::UpdateStripe(UObject* Object) const
{
	GUARD(ListView != nullptr);
	if(Stripe != nullptr)
	{
		Stripe->SetIsVisible(IsListItemSelected());
	}
}
