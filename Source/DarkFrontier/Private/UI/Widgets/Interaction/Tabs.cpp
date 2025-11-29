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
	SetTabs(Tabs);
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
	UTab* Previous = ListView->GetSelectedItem<UTab>();
	SetTabsWithInitial(InTabs, Previous);
}

void UTabs::SetTabsWithInitial(const TArray<UTab*>& InTabs, UTab* Initial)
{
	if(!InTabs.Contains(Initial))
	{
		Initial = InTabs.Num() > 0 ? InTabs[0] : nullptr;
	}
	
	Tabs = InTabs;
	ListView->SetListItems(Tabs);
	if(IsValid(Initial))
	{
		ListView->SetSelectedItem(Initial);
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

void UTabs::HandleTabSelected(UObject* Obj) const
{
	const UTab* Tab = Cast<UTab>(Obj);
	if(Tab == nullptr)
	{
		TabStack->ClearWidgets();
		return;
	}
	UUIFunctionLibrary::ReplaceWidget(TabStack, Tab->WidgetClass);
}

void UTabs::HandleWidgetChanged(UCommonActivatableWidget* Widget) const
{
	OnTabChanged.Broadcast(Widget);
}
