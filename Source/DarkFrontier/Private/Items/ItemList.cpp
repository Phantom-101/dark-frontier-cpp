// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemList.h"
#include "Items/Item.h"

TArray<FItemStack> UItemList::GetStacks() const
{
	return Stacks;
}

bool UItemList::GetStack(UItem* Item, FItemStack& OutStack) const
{
	for(const FItemStack& Stack : Stacks)
	{
		if(Stack.Item == Item)
		{
			OutStack = Stack;
			return true;
		}
	}
	return false;
}

TArray<UItem*> UItemList::GetItems() const
{
	TArray<UItem*> Items;
	for(const FItemStack& Stack : Stacks)
	{
		Items.Add(Stack.Item);
	}
	return Items;
}

int UItemList::GetQuantity(UItem* Item) const
{
	FItemStack Stack;
	if(GetStack(Item, Stack))
	{
		return Stack.Quantity;
	}
	return 0;
}

int UItemList::HasQuantity(UItem* Item, const int Quantity) const
{
	return GetQuantity(Item) >= Quantity;
}

void UItemList::SetQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr)
	check(Quantity >= 0)
	
	FItemStack Stack;
	if(GetStack(Item, Stack))
	{
		Stacks.RemoveSwap(Stack);
	}
	if(Quantity > 0)
	{
		Stacks.Add(FItemStack(Item, Quantity));
	}
}

void UItemList::AddQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr)
	check(Quantity >= 0)

	SetQuantity(Item, GetQuantity(Item) + Quantity);
}

void UItemList::RemoveQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr)
	check(Quantity >= 0)
	check(HasQuantity(Item, Quantity))

	SetQuantity(Item, GetQuantity(Item) - Quantity);
}

float UItemList::GetTotalVolume() const
{
	float Volume = 0;
	for(const FItemStack& Stack : Stacks)
	{
		Volume += Stack.Item->Volume * Stack.Quantity;
	}
	return Volume;
}

float UItemList::GetVolume(UItem* Item) const
{
	return GetQuantity(Item) * Item->Volume;
}

float UItemList::GetTotalMass() const
{
	float Mass = 0;
	for(const FItemStack& Stack : Stacks)
	{
		Mass += Stack.Item->Mass * Stack.Quantity;
	}
	return Mass;
}

float UItemList::GetMass(UItem* Item) const
{
	return GetQuantity(Item) * Item->Mass;
}

bool UItemList::HasList(UItemList* Other) const
{
	check(Other != nullptr)
	
	for(const FItemStack& Stack : Other->Stacks)
	{
		if(GetQuantity(Stack.Item) < Stack.Quantity)
		{
			return false;
		}
	}
	return true;
}

void UItemList::SetList(UItemList* Other)
{
	check(Other != nullptr)
	
	Stacks.Empty();
	for(const FItemStack& Stack : Other->Stacks)
	{
		Stacks.Add(Stack);
	}
}

void UItemList::AddList(UItemList* Other)
{
	check(Other != nullptr)

	for(const FItemStack& Stack : Other->Stacks)
	{
		AddQuantity(Stack.Item, Stack.Quantity);
	}
}

void UItemList::RemoveList(UItemList* Other)
{
	check(Other != nullptr)
	check(HasList(Other))

	for(const FItemStack& Stack : Other->Stacks)
	{
		RemoveQuantity(Stack.Item, Stack.Quantity);
	}
}
