// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemList.h"
#include "Items/Item.h"

TArray<FItemStack> UItemList::GetStacks() const
{
	return Stacks;
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
	check(Item != nullptr);
	
	FItemStack Stack;
	if(GetStack(Item, Stack))
	{
		return Stack.Quantity;
	}
	return 0;
}

int UItemList::HasQuantity(UItem* Item, const int Quantity) const
{
	check(Item != nullptr);

	if(!ensure(Quantity >= 0))
	{
		return true;
	}
	
	return GetQuantity(Item) >= Quantity;
}

bool UItemList::SetQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr);

	if(!ensure(Quantity >= 0))
	{
		return false;
	}
	
	FItemStack Stack;
	if(GetStack(Item, Stack))
	{
		Stacks.RemoveSwap(Stack);
	}
	if(Quantity > 0)
	{
		Stacks.Add(FItemStack(Item, Quantity));
	}
	OnChanged.Broadcast();
	return true;
}

bool UItemList::AddQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr)

	if(!ensure(Quantity >= 0))
	{
		return false;
	}

	return SetQuantity(Item, GetQuantity(Item) + Quantity);
}

bool UItemList::RemoveQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr)

	if(!ensure(Quantity >= 0))
	{
		return false;
	}
	
	if(!ensure(HasQuantity(Item, Quantity)))
	{
		return false;
	}

	return SetQuantity(Item, GetQuantity(Item) - Quantity);
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
	check(Item != nullptr);
	
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
	check(Item != nullptr);
	
	return GetQuantity(Item) * Item->Mass;
}

bool UItemList::HasList(UItemList* Other) const
{
	check(Other != nullptr);
	
	for(const FItemStack& Stack : Other->Stacks)
	{
		if(GetQuantity(Stack.Item) < Stack.Quantity)
		{
			return false;
		}
	}
	return true;
}

bool UItemList::SetList(UItemList* Other)
{
	check(Other != nullptr);
	
	Stacks.Empty();
	for(const FItemStack& Stack : Other->Stacks)
	{
		Stacks.Add(Stack);
	}
	OnChanged.Broadcast();
	return true;
}

bool UItemList::AddList(UItemList* Other)
{
	check(Other != nullptr);

	for(const FItemStack& Stack : Other->Stacks)
	{
		if(!AddQuantity(Stack.Item, Stack.Quantity))
		{
			return false;
		}
	}
	return true;
}

bool UItemList::RemoveList(UItemList* Other)
{
	check(Other != nullptr);

	if(!ensure(HasList(Other)))
	{
		return false;
	}

	for(const FItemStack& Stack : Other->Stacks)
	{
		if(!RemoveQuantity(Stack.Item, Stack.Quantity))
		{
			return false;
		}
	}
	return true;
}

bool UItemList::GetStack(UItem* Item, FItemStack& OutStack) const
{
	check(Item != nullptr);
	
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
