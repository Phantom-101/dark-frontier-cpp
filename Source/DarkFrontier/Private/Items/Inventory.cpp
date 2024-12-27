// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"

TArray<FItemStack> UInventory::GetStacks()
{
	return ItemStacks;
}

TArray<UItem*> UInventory::GetItems()
{
	TArray<UItem*> Items;
	for(const FItemStack& Stack : ItemStacks)
	{
		if(!Items.Contains(Stack.Item))
		{
			Items.Add(Stack.Item);
		}
	}
	return Items;
}

int UInventory::GetQuantity()
{
	int Quantity = 0;
	for(const FItemStack& Stack : ItemStacks)
	{
		Quantity += Stack.Quantity;
	}
	return Quantity;
}

int UInventory::GetItemQuantity(UItem* Item)
{
	for(const FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			return Stack.Quantity;
		}
	}
	return 0;
}

float UInventory::GetVolume()
{
	float Volume = 0;
	for(const FItemStack& Stack : ItemStacks)
	{
		Volume += Stack.GetVolume();
	}
	return Volume;
}

float UInventory::GetItemVolume(UItem* Item)
{
	for(const FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			return Stack.GetVolume();
		}
	}
	return 0;
}

float UInventory::GetMass()
{
	float Mass = 0;
	for(const FItemStack& Stack : ItemStacks)
	{
		Mass += Stack.GetMass();
	}
	return Mass;
}

float UInventory::GetItemMass(UItem* Item)
{
	for(const FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			return Stack.GetMass();
		}
	}
	return 0;
}

bool UInventory::CanFit(const int ExtraVolume, const int ExtraMass)
{
	return GetVolume() + ExtraVolume <= MaxVolume && GetMass() + ExtraMass <= MaxMass;
}

bool UInventory::AddItems(UItem* Item, const int Quantity)
{
	const float ExtraVolume = Item->Volume * Quantity;
	const float ExtraMass = Item->Mass * Quantity;

	if(!CanFit(ExtraVolume, ExtraMass)) return false;

	for(FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			Stack.Quantity += Quantity;
			OnItemChanged.Broadcast(Item, Stack.Quantity);
			return true;
		}
	}

	ItemStacks.Add(FItemStack(Item, Quantity));
	OnItemAdded.Broadcast(Item, Quantity);
	return true;
}

bool UInventory::RemoveItems(UItem* Item, int Quantity)
{
	const FItemStack* Found = nullptr;
	for(FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			if(Stack.Quantity < Quantity)
			{
				// Not enough
				return false;
			}
			
			Stack.Quantity -= Quantity;
			Found = &Stack;
			
			break;
		}
	}

	if(Found == nullptr)
	{
		// Item does not exist
		return false;
	}

	// Remove stack if depleted
	if(Found->Quantity == 0)
	{
		ItemStacks.RemoveSingle(*Found);
		OnItemRemoved.Broadcast(Item);
	}
	else
	{
		OnItemChanged.Broadcast(Item, Found->Quantity);
	}
	
	return true;
}
