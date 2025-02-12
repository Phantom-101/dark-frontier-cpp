// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/Tabs.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Widgets/Interaction/ListBox.h"
#include "UI/Widgets/Interaction/Tab.h"
#include "UI/Widgets/Interaction/TabOption.h"

void UTabs::NativeConstruct()
{
	Super::NativeConstruct();
	
	for(TSubclassOf<UTab> TabClass : TabClasses)
	{
		UTab* Tab = CreateWidget<UTab>(this, TabClass);
		TabSwitcher->AddChild(Tab);
		Tabs.Add(Tab);
	}

	TabListBox->SetBuilder([Owner = this, Class = TabOptionClass](UObject* Tab)
	{
		UTabOption* Option = CreateWidget<UTabOption>(Owner, Class);
		Option->Init(Cast<UTab>(Tab));
		return Option;
	});
	TabListBox->SetOptions(TArray<UObject*>(Tabs));
	TabListBox->OnChanged.AddUObject<UTabs>(this, &UTabs::HandleTabSelected);
}

void UTabs::HandleTabSelected(UObject* Tab) const
{
	if(TabListBox->IsCurrentOptionValid())
	{
		for(UWidget* Widget : TabSwitcher->GetAllChildren())
		{
			if(Widget == Tab)
			{
				TabSwitcher->SetActiveWidget(Widget);
				return;
			}
		}
	}
	else
	{
		TabSwitcher->SetActiveWidgetIndex(0);
	}
}
