﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemPod.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Structures/Structure.h"

AItemPod::AItemPod()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

	Location = CreateDefaultSubobject<USectorLocation>("Location");
	Targetable = CreateDefaultSubobject<UTargetable>("Targetable");
}

void AItemPod::Init(UItem* InItem, const int InQuantity)
{
	Item = InItem;
	Quantity = InQuantity;
}

void AItemPod::BeginPlay()
{
	Super::BeginPlay();

	if(!IsValid(Item) || Quantity <= 0)
	{
		Destroy();
	}
}

UItem* AItemPod::GetItem() const
{
	return Item;
}

int AItemPod::GetQuantity() const
{
	return Quantity;
}

void AItemPod::AddToInventory(UInventory* Inventory)
{
	check(Inventory != nullptr);

	const int VolumeEquivalent = FMath::FloorToInt(Inventory->GetFreeVolume() / Item->Volume);
	const int MassEquivalent = FMath::FloorToInt(Inventory->GetFreeMass() / Item->Mass);
	const int ToAdd = FMath::Min3(Quantity, VolumeEquivalent, MassEquivalent);

	Quantity -= ToAdd;
	Inventory->AddQuantity(Item, ToAdd);

	if(Quantity <= 0)
	{
		Destroy();
	}
}

UStaticMeshComponent* AItemPod::GetStaticMesh() const
{
	return StaticMesh;
}

USectorLocation* AItemPod::GetSectorLocation() const
{
	return Location;
}

UTargetable* AItemPod::GetTargetable() const
{
	return Targetable;
}
