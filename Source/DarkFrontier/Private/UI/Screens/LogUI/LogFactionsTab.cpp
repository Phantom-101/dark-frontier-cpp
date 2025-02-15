// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogFactionsTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Screens/LogUI/FactionOption.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogFactionsTab::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> Factions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFaction::StaticClass(), Factions);
	FactionListBox->SetOptions(TArray<UObject*>(Factions));
	FactionListBox->SetBuilder([Owner = this, Class = OptionClass](UObject* Faction)
	{
		UFactionOption* Option = CreateWidget<UFactionOption>(Owner, Class);
		Option->Init(Cast<AFaction>(Faction));
		return Option;
	});

	FactionListBox->OnChanged.AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleBack);
}

void ULogFactionsTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		Switcher->SetActiveWidgetIndex(0);
	}
	else
	{
		Switcher->SetActiveWidgetIndex(1);
		NameText->SetText(Cast<AFaction>(Object)->GetFactionName());
	}
}

void ULogFactionsTab::HandleBack() const
{
	FactionListBox->SetCurrentOption(nullptr);
}
