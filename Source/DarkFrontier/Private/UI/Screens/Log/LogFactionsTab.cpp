// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogFactionsTab.h"
#include "CommonButtonBase.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Screens/Log/FactionEntry.h"
#include "UI/Screens/Log/FactionInfo.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogFactionsTab::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> Factions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFaction::StaticClass(), Factions);
	FactionListBox->SetOptions(TArray<UObject*>(Factions));
	FactionListBox->SetBuilder([Owner = this, Class = EntryClass](UObject* Faction)
	{
		UFactionEntry* Option = CreateWidget<UFactionEntry>(Owner, Class);
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
		FactionInfo->Init(Cast<AFaction>(Object));
	}
}

void ULogFactionsTab::HandleBack() const
{
	FactionListBox->SetCurrentOption(nullptr);
}
