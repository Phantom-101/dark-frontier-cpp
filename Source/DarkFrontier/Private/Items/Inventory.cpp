// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"

TArray<FItemStack> UInventory::GetStacks()
{
	return ItemStacks;
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

float UInventory::GetValue()
{
	float Value = 0;
	for(const FItemStack& Stack : ItemStacks)
	{
		Value += Stack.Value;
	}
	return Value;
}

float UInventory::GetItemValue(UItem* Item)
{
	for(const FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			return Stack.Value;
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

bool UInventory::AddItems(UItem* Item, const int Quantity, const float Value)
{
	const float ExtraVolume = Item->Volume * Quantity;
	const float ExtraMass = Item->Mass * Quantity;

	if(!CanFit(ExtraVolume, ExtraMass)) return false;

	for(FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			Stack.Quantity += Quantity;
			Stack.Value += Value;
			return true;
		}
	}

	ItemStacks.Add(FItemStack(Item, Quantity, Value));
	
	return true;
}

bool UInventory::AddStack(const FItemStack& InStack)
{
	return AddItems(InStack.Item, InStack.Quantity, InStack.Value);
}

bool UInventory::RemoveItems(UItem* Item, int Quantity, float& Value)
{
	const FItemStack* ToRemove = nullptr;
	for(FItemStack& Stack : ItemStacks)
	{
		if(Stack.Item == Item)
		{
			if(Stack.Quantity < Quantity)
			{
				// Not enough
				return false;
			}

			const float RemovedValue = Stack.Value * Quantity / Stack.Quantity;
			
			Stack.Quantity -= Quantity;
			Stack.Value -= RemovedValue;
			Value += RemovedValue;

			if(Stack.Quantity == 0)
			{
				// Mark stack for removal
				ToRemove = &Stack;
			}
			
			break;
		}
	}

	if(ToRemove == nullptr)
	{
		// Item does not exist
		return false;
	}

	ItemStacks.RemoveSingle(*ToRemove);
	return true;
}

bool UInventory::RemoveStack(const FItemStack& InStack)
{
	return ItemStacks.RemoveSingle(InStack) == 1;
}
