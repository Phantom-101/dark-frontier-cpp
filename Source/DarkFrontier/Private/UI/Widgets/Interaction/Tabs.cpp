// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/Tabs.h"
#include "CommonActivatableWidget.h"
#include "Components/ListView.h"
#include "Libraries/UIFunctionLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

bool UTab::IsValid() const
{
	return ::IsValid(WidgetClass);
}

void UTabs::NativeConstruct()
{
	Super::NativeConstruct();

	ListView->OnItemSelectionChanged().AddUObject(this, &UTabs::HandleTabSelected);
	TabStack->OnDisplayedWidgetChanged().AddUObject(this, &UTabs::HandleWidgetChanged);

	// Select the first tab after registering selection callback so the UI gets updated
	if(!Tabs.IsEmpty())
	{
		SetTabs(Tabs);
	}
}

void UTabs::NativeDestruct()
{
	Super::NativeDestruct();

	ListView->OnItemSelectionChanged().RemoveAll(this);
	TabStack->OnDisplayedWidgetChanged().RemoveAll(this);

	SetTabs(TArray<UTab*>());
}

const TArray<TObjectPtr<UTab>>& UTabs::GetTabs() const
{
	return Tabs;
}

void UTabs::SetTabs(const TArray<UTab*>& InTabs)
{
	Tabs = InTabs;

	UTab* Previous = ListView->GetSelectedItem<UTab>();
	ListView->SetListItems(Tabs);
	if(IsValid(Previous) && Tabs.Contains(Previous))
	{
		ListView->SetSelectedItem(Previous);
	}
	else if(Tabs.Num() > 0)
	{
		ListView->SetSelectedItem(Tabs[0]);
	}
}

UTab* UTabs::GetTab() const
{
	return ListView->GetSelectedItem<UTab>();
}

UCommonActivatableWidget* UTabs::GetTabWidget() const
{
	return TabStack->GetActiveWidget();
}

void UTabs::HandleTabSelected(UObject* Tab) const
{
	if(Tab == nullptr)
	{
		TabStack->ClearWidgets();
		return;
	}
	
	const TSubclassOf<UCommonActivatableWidget> WidgetClass = Cast<UTab>(Tab)->WidgetClass;
	if(IsValid(TabStack->GetActiveWidget()) && TabStack->GetActiveWidget()->GetClass() == WidgetClass)
	{
		// Skip replacing widget if active widget is already of the correct class
		// We do this to prevent cases where the tabs list is changed, but the selected tab
		// still exists in the new list, in which case it gets popped and pushed,
		// causing the UI to fade in and out for no reason
		return;
	}
	UUIFunctionLibrary::ReplaceWidget(TabStack, WidgetClass);
}

void UTabs::HandleWidgetChanged(UCommonActivatableWidget* Widget) const
{
	OnTabChanged.Broadcast(Widget);
}
