// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemList.h"
#include "Items/Item.h"

TArray<UItem*> UItemList::GetItems() const
{
	TArray<UItem*> Items;
	for(const TPair<TObjectPtr<UItem>, int>& Pair : Quantities)
	{
		if(Pair.Value > 0)
		{
			Items.Add(Pair.Key);
		}
	}
	return Items;
}

int UItemList::GetQuantity(UItem* Item) const
{
	check(IsValid(Item));

	return Quantities.Contains(Item) ? Quantities[Item] : 0;
}

int UItemList::HasQuantity(UItem* Item, const int Quantity) const
{
	check(IsValid(Item));

	if(!ensure(Quantity >= 0))
	{
		return true;
	}

	return GetQuantity(Item) >= Quantity;
}

bool UItemList::SetQuantity(UItem* Item, const int Quantity)
{
	check(IsValid(Item));

	if(!ensure(Quantity >= 0))
	{
		return false;
	}

	Quantities.Add(Item, Quantity);
	OnChanged.Broadcast();
	return true;
}

bool UItemList::AddQuantity(UItem* Item, const int Quantity)
{
	check(IsValid(Item));

	if(!ensure(Quantity >= 0))
	{
		return false;
	}

	return SetQuantity(Item, GetQuantity(Item) + Quantity);
}

bool UItemList::RemoveQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr);

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
	for(const TPair<TObjectPtr<UItem>, int>& Pair : Quantities)
	{
		Volume += Pair.Key->Volume * Pair.Value;
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
	for(const TPair<TObjectPtr<UItem>, int>& Pair : Quantities)
	{
		Mass += Pair.Key->Mass * Pair.Value;
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

	for(const TPair<TObjectPtr<UItem>, int>& Pair : Other->Quantities)
	{
		if(GetQuantity(Pair.Key) < Pair.Value)
		{
			return false;
		}
	}
	return true;
}

bool UItemList::SetList(UItemList* Other)
{
	check(Other != nullptr);

	Quantities.Empty();
	for(const TPair<TObjectPtr<UItem>, int>& Pair : Other->Quantities)
	{
		Quantities.Add(Pair);
	}
	OnChanged.Broadcast();
	return true;
}

bool UItemList::AddList(UItemList* Other)
{
	check(Other != nullptr);

	const TMap<TObjectPtr<UItem>, int> Restore = Quantities;
	for(const TPair<TObjectPtr<UItem>, int>& Pair : Other->Quantities)
	{
		if(!AddQuantity(Pair.Key, Pair.Value))
		{
			Quantities = Restore;
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

	for(const TPair<TObjectPtr<UItem>, int>& Pair : Other->Quantities)
	{
		if(!RemoveQuantity(Pair.Key, Pair.Value))
		{
			return false;
		}
	}
	return true;
}
