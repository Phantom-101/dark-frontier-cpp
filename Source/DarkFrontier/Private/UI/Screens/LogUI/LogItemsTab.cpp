// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogItemsTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UniverseGameMode.h"
#include "Items/Item.h"
#include "UI/Screens/InventoryUI/ItemEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogItemsTab::NativeConstruct()
{
	Super::NativeConstruct();
	
	TArray<UItem*> Items = Cast<AUniverseGameMode>(GetWorld()->GetAuthGameMode())->GetAllowedItems();

	TArray<UObject*> ItemObjects;
	for(UItem* Item : Items)
	{
		UItemObject* Obj = NewObject<UItemObject>();
		Obj->Item = Item;
		ItemObjects.Add(Obj);
	}
	
	ItemListBox->SetOptions(ItemObjects);
	ItemListBox->SetBuilder([Owner = this, Class = EntryClass](UObject* Item)
	{
		UItemEntry* Option = CreateWidget<UItemEntry>(Owner, Class);
		Option->Init(Cast<UItemObject>(Item));
		return Option;
	});

	ItemListBox->OnChanged.AddUObject<ULogItemsTab>(this, &ULogItemsTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogItemsTab>(this, &ULogItemsTab::HandleBack);
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
		NameText->SetText(Cast<UItemObject>(Object)->Item->Name);
	}
}

void ULogItemsTab::HandleBack() const
{
	ItemListBox->SetCurrentOption(nullptr);
}
