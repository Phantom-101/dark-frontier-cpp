// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogFactionsTab.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Screens/Log/LogFactionInfo.h"

void ULogFactionsTab::NativeConstruct()
{
	Super::NativeConstruct();
	
	ListView->OnItemSelectionChanged().AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogFactionsTab>(this, &ULogFactionsTab::HandleBack);
}

void ULogFactionsTab::NativeOnActivated()
{
	Super::NativeOnActivated();

	UE_LOG(LogDarkFrontier, Log, TEXT("On activated"));
	UE_LOG(LogDarkFrontier, Log, TEXT("%d"), ListView->GetListItems().Num());

	const AFaction* Selected = ListView->GetSelectedItem<AFaction>();

	if(Selected != nullptr)
	{
		UE_LOG(LogDarkFrontier, Log, TEXT("%s"), *Selected->GetFactionName().ToString());
	}

	TArray<AActor*> Factions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFaction::StaticClass(), Factions);
	ListView->SetListItems(Factions);

	ListView->SetSelectedItem(Selected);
}

void ULogFactionsTab::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	UE_LOG(LogDarkFrontier, Log, TEXT("On deactivated"));
	UE_LOG(LogDarkFrontier, Log, TEXT("%d"), ListView->GetListItems().Num());

	const AFaction* Selected = ListView->GetSelectedItem<AFaction>();

	if(Selected != nullptr)
	{
		UE_LOG(LogDarkFrontier, Log, TEXT("%s"), *Selected->GetFactionName().ToString());
	}
}

void ULogFactionsTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		UE_LOG(LogDarkFrontier, Log, TEXT("handle deselect"));
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
	ListView->ClearSelection();
}
