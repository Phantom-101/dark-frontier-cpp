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

	ListView->SetListItems(Tabs);
	ListView->OnItemSelectionChanged().AddUObject(this, &UTabs::HandleTabSelected);
	TabStack->OnDisplayedWidgetChanged().AddUObject(this, &UTabs::HandleWidgetChanged);

	if(Tabs.Num() > 0)
	{
		// Select the first tab via selection callback so the UI gets updated as well
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
	UUIFunctionLibrary::ReplaceWidget(TabStack, Cast<UTab>(Tab)->WidgetClass);
}

void UTabs::HandleWidgetChanged(UCommonActivatableWidget* Widget) const
{
	OnTabChanged.Broadcast(Widget);
}
