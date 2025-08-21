// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogItemsTab.h"
#include "CommonButtonBase.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UniverseGameMode.h"
#include "Items/Item.h"
#include "UI/Screens/Log/LogItemInfo.h"

void ULogItemsTab::NativeConstruct()
{
	Super::NativeConstruct();
	
	ListView->OnItemSelectionChanged().AddUObject<ULogItemsTab>(this, &ULogItemsTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogItemsTab>(this, &ULogItemsTab::HandleBack);
}

void ULogItemsTab::NativeOnActivated()
{
	Super::NativeOnActivated();

	const UObject* Selected = ListView->GetSelectedItem();

	const TArray<UItem*> Items = GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetItemList();
	ListView->SetListItems(Items);

	ListView->SetSelectedItem(Selected);
}

void ULogItemsTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		Switcher->SetActiveWidgetIndex(0);
	}
	else
	{
		Switcher->SetActiveWidgetIndex(1);
		ItemInfo->Init(Cast<UItem>(Object));
	}
}

void ULogItemsTab::HandleBack() const
{
	ListView->ClearSelection();
}
