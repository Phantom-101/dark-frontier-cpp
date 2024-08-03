// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/ItemList.h"
#include "Components/ListView.h"
#include "Items/Inventory.h"
#include "Items/ItemStack.h"
#include "UI/Screens/InventoryUI/ItemEntryObject.h"

UInventory* UItemList::GetInventory() const
{
	return Inventory;
}

void UItemList::SetInventory(UInventory* InInventory)
{
	if(IsValid(Inventory))
	{
		Inventory->OnItemAdded.RemoveAll(this);
		Inventory->OnItemRemoved.RemoveAll(this);
	}
	
	Inventory = InInventory;

	if(IsValid(Inventory))
	{
		Inventory->OnItemAdded.AddUObject<UItemList>(this, &UItemList::AddItem);
		Inventory->OnItemRemoved.AddUObject<UItemList>(this, &UItemList::RemoveItem);
	}

	UpdateAll();
}

UItem* UItemList::GetSelectedItem() const
{
	return SelectedItem;
}

void UItemList::SetSelectedItem(UItem* InItem)
{
	if(IsValid(Inventory) && Inventory->GetItemQuantity(InItem) > 0)
	{
		SelectedItem = InItem;
	}
}

void UItemList::UpdateAll() const
{
	ItemList->ClearListItems();
	for(const FItemStack& Stack : Inventory->GetStacks())
	{
		UItemEntryObject* Object = NewObject<UItemEntryObject>();
		Object->Inventory = Inventory;
		Object->Item = Stack.Item;
		ItemList->AddItem(Object);
	}
	ItemList->RegenerateAllEntries();
}

void UItemList::AddItem(UItem* Item, int Initial) const
{
	UItemEntryObject* Object = NewObject<UItemEntryObject>();
	Object->Inventory = Inventory;
	Object->Item = Item;
	ItemList->AddItem(Object);
}

void UItemList::RemoveItem(UItem* Item) const
{
	const TArray<UObject*> Objects = ItemList->GetListItems();
	for(int Index = 0; Index < Objects.Num(); Index++)
	{
		if(Cast<UItemEntryObject>(Objects[Index])->Item == Item)
		{
			ItemList->RemoveItem(Objects[Index]);
			return;
		}
	}
}
