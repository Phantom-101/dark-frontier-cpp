// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemList.h"
#include "Items/ItemStack.h"
#include "Structures/Structure.h"

UInventory::UInventory()
{
	Items = CreateDefaultSubobject<UItemList>("Items");
}

AStructure* UInventory::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}

TArray<FItemStack> UInventory::GetStacks() const
{
	return Items->GetStacks();
}

bool UInventory::GetStack(UItem* Item, FItemStack& OutStack) const
{
	return Items->GetStack(Item, OutStack);
}

TArray<UItem*> UInventory::GetItems() const
{
	return Items->GetItems();
}

int UInventory::GetQuantity(UItem* Item) const
{
	return Items->GetQuantity(Item);
}

int UInventory::HasQuantity(UItem* Item, const int Quantity) const
{
	return Items->HasQuantity(Item, Quantity);
}

int UInventory::FitsQuantity(const UItem* Item, const int Quantity) const
{
	check(Item != nullptr)
	
	return GetTotalVolume() + Item->Volume * Quantity <= MaxVolume && GetTotalMass() + Item->Mass * Quantity <= MaxMass;
}

void UInventory::SetQuantity(UItem* Item, const int Quantity) const
{
	check(Item != nullptr)
	check(Quantity >= 0)
	check(FitsQuantity(Item, Quantity - GetQuantity(Item)))
	
	Items->SetQuantity(Item, Quantity);
	OnItemsChanged.Broadcast();
}

void UInventory::AddQuantity(UItem* Item, const int Quantity) const
{
	check(Item != nullptr)
	check(Quantity >= 0)
	check(FitsQuantity(Item, Quantity))
	
	Items->AddQuantity(Item, Quantity);
	OnItemsChanged.Broadcast();
}

void UInventory::RemoveQuantity(UItem* Item, const int Quantity) const
{
	check(Item != nullptr)
	check(Quantity >= 0)
	check(HasQuantity(Item, Quantity))
	
	Items->RemoveQuantity(Item, Quantity);
	OnItemsChanged.Broadcast();
}

float UInventory::GetMaxVolume() const
{
	return MaxVolume;
}

float UInventory::GetTotalVolume() const
{
	return Items->GetTotalVolume();
}

float UInventory::GetFreeVolume() const
{
	return MaxVolume - GetTotalVolume();
}

float UInventory::GetVolume(UItem* Item) const
{
	return Items->GetVolume(Item);
}

float UInventory::GetMaxMass() const
{
	return MaxMass;
}

float UInventory::GetTotalMass() const
{
	return Items->GetTotalMass();
}

float UInventory::GetFreeMass() const
{
	return MaxMass - GetTotalMass();
}

float UInventory::GetMass(UItem* Item) const
{
	return Items->GetMass(Item);
}

UItemList* UInventory::GetList() const
{
	UItemList* List = NewObject<UItemList>();
	List->SetList(Items);
	return List;
}

bool UInventory::HasList(UItemList* Other) const
{
	check(Other != nullptr)
	
	return Items->HasList(Other);
}

bool UInventory::FitsList(const UItemList* Other) const
{
	check(Other != nullptr)
	
	return GetTotalVolume() + Other->GetTotalVolume() <= MaxVolume && GetTotalMass() + Other->GetTotalMass() <= MaxMass;
}

void UInventory::SetList(UItemList* Other) const
{
	check(Other != nullptr)
	check(Other->GetTotalVolume() <= MaxVolume && Other->GetTotalMass() <= MaxMass)

	Items->SetList(Other);
	OnItemsChanged.Broadcast();
}

void UInventory::AddList(UItemList* Other) const
{
	check(Other != nullptr)
	check(FitsList(Other))

	Items->AddList(Other);
	OnItemsChanged.Broadcast();
}

void UInventory::RemoveList(UItemList* Other) const
{
	check(Other != nullptr)
	check(HasList(Other))

	Items->RemoveList(Other);
	OnItemsChanged.Broadcast();
}
