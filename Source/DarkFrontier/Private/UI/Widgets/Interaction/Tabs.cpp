// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/Tabs.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Widgets/Interaction/ListBox.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "UI/Widgets/Interaction/TabEntry.h"

void UTabs::NativeConstruct()
{
	Super::NativeConstruct();

	TabSwitcher->ClearChildren();
	Tabs.Empty();
	
	for(TSubclassOf<UTab> TabClass : TabClasses)
	{
		UTab* Tab = CreateWidget<UTab>(this, TabClass);
		TabSwitcher->AddChild(Tab);
		Tabs.Add(Tab);
	}

	TabListBox->SetOptions(TArray<UObject*>(Tabs));
	TabListBox->SetBuilder([Owner = this, Class = TabEntryClass](UObject* Tab)
	{
		UTabEntry* Option = CreateWidget<UTabEntry>(Owner, Class);
		Option->Init(Cast<UTab>(Tab));
		return Option;
	});
	
	TabListBox->OnChanged.AddUObject<UTabs>(this, &UTabs::HandleTabSelected);
}

void UTabs::HandleTabSelected(UObject* Tab) const
{
	if(TabListBox->IsCurrentOptionValid())
	{
		TabSwitcher->SetActiveWidget(Cast<UWidget>(Tab));
	}
	else
	{
		TabSwitcher->SetActiveWidgetIndex(0);
	}
}
