// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemList.h"

int UInventory::FitsQuantity(const UItem* Item, const int Quantity) const
{
	check(Item != nullptr);

	return GetTotalVolume() + Item->Volume * Quantity <= MaxVolume && GetTotalMass() + Item->Mass * Quantity <= MaxMass;
}

bool UInventory::SetQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr);
	check(Quantity >= 0);

	if(!ensure(FitsQuantity(Item, Quantity - GetQuantity(Item))))
	{
		return false;
	}

	return Super::SetQuantity(Item, Quantity);
}

bool UInventory::AddQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr);
	check(Quantity >= 0);

	if(!ensure(FitsQuantity(Item, Quantity)))
	{
		return false;
	}

	return Super::AddQuantity(Item, Quantity);
}

bool UInventory::RemoveQuantity(UItem* Item, const int Quantity)
{
	check(Item != nullptr);
	check(Quantity >= 0);

	if(!ensure(HasQuantity(Item, Quantity)))
	{
		return false;
	}

	return Super::RemoveQuantity(Item, Quantity);
}

float UInventory::GetMaxVolume() const
{
	return MaxVolume;
}

float UInventory::GetTotalVolume01() const
{
	return GetTotalVolume() / MaxVolume;
}

float UInventory::GetFreeVolume() const
{
	return MaxVolume - GetTotalVolume();
}

float UInventory::GetFreeVolume01() const
{
	return 1 - GetTotalVolume01();
}

float UInventory::GetMaxMass() const
{
	return MaxMass;
}

float UInventory::GetTotalMass01() const
{
	return GetTotalMass() / MaxMass;
}

float UInventory::GetFreeMass() const
{
	return MaxMass - GetTotalMass();
}

float UInventory::GetFreeMass01() const
{
	return 1 - GetTotalMass01();
}

bool UInventory::FitsList(const UItemList* Other) const
{
	check(Other != nullptr);

	return GetTotalVolume() + Other->GetTotalVolume() <= MaxVolume && GetTotalMass() + Other->GetTotalMass() <= MaxMass;
}

bool UInventory::SetList(UItemList* Other)
{
	check(Other != nullptr);

	if(!ensure(Other->GetTotalVolume() <= MaxVolume && Other->GetTotalMass() <= MaxMass))
	{
		return false;
	}

	return Super::SetList(Other);
}

bool UInventory::AddList(UItemList* Other)
{
	check(Other != nullptr);

	if(!ensure(FitsList(Other)))
	{
		return false;
	}

	return Super::AddList(Other);
}

bool UInventory::RemoveList(UItemList* Other)
{
	check(Other != nullptr);

	if(!ensure(HasList(Other)))
	{
		return false;
	}

	return Super::RemoveList(Other);
}
