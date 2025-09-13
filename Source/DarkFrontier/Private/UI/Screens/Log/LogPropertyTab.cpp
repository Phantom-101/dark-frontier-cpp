// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogPropertyTab.h"
#include "CommonButtonBase.h"
#include "EngineUtils.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "UI/Screens/Log/LogPropertyInfo.h"

void ULogPropertyTab::NativeConstruct()
{
	Super::NativeConstruct();

	ListView->OnItemSelectionChanged().AddUObject<ULogPropertyTab>(this, &ULogPropertyTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogPropertyTab>(this, &ULogPropertyTab::HandleBack);
}

void ULogPropertyTab::NativeOnActivated()
{
	Super::NativeOnActivated();

	const UObject* Selected = ListView->GetSelectedItem();

	const AFaction* PlayerFaction = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetAffiliation()->GetFaction();
	TArray<UObject*> Structures;
	for(TActorIterator<AStructure> Itr(GetWorld()); Itr; ++Itr)
	{
		if(Itr->GetAffiliation()->GetFaction() == PlayerFaction)
		{
			Structures.Add(*Itr);
		}
	}
	ListView->SetListItems(TArray(Structures));

	ListView->SetSelectedItem(Selected);
}

void ULogPropertyTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		Switcher->SetActiveWidgetIndex(0);
	}
	else
	{
		Switcher->SetActiveWidgetIndex(1);
		PropertyInfo->Init(Cast<AStructure>(Object));
	}
}

void ULogPropertyTab::HandleBack() const
{
	ListView->ClearSelection();
}
