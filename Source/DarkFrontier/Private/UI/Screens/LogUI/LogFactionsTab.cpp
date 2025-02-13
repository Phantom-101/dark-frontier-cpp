// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogFactionsTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogFactionsTab::NativeConstruct()
{
	Super::NativeConstruct();

	FactionListBox->OnChanged.AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleBack);
}

void ULogFactionsTab::HandleSelect(UObject* Object) const
{
	Switcher->SetActiveWidgetIndex(1);
	NameText->SetText(Cast<AFaction>(Object)->GetFactionName());
}

void ULogFactionsTab::HandleBack() const
{
	Switcher->SetActiveWidgetIndex(0);
	FactionListBox->SetCurrentOption(nullptr);
}
