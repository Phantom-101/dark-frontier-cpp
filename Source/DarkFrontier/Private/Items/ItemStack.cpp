// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemStack.h"
#include "Items/Item.h"

FItemStack::FItemStack()
{
}

FItemStack::FItemStack(UItem* InItem, const int InQuantity)
{
	Item = InItem;
	Quantity = InQuantity;
}

float FItemStack::GetVolume() const
{
	return Quantity * Item->Volume;
}

float FItemStack::GetMass() const
{
	return Quantity * Item->Mass;
}

bool FItemStack::IsValid() const
{
	return Item != nullptr && Quantity > 0;
}

bool FItemStack::operator==(const FItemStack& Other) const
{
	return Item == Other.Item && Quantity == Other.Quantity;
}
