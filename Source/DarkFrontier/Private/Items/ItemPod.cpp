// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemPod.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Sectors/Sector.h"
#include "Structures/Structure.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/Flight/Selectors/ItemPodSelector.h"

AItemPod::AItemPod()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

void AItemPod::Init(UItem* InItem, const int InQuantity)
{
	Item = InItem;
	Quantity = InQuantity;
}

void AItemPod::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Sector))
	{
		Sector->RegisterItemPod(this);
	}

	if(!IsValid(Item) || Quantity <= 0)
	{
		Destroy();
	}
}

void AItemPod::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(IsValid(Sector))
	{
		Sector->UnregisterItemPod(this);
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

bool AItemPod::IsTargetable(AStructure* Structure) const
{
	return Structure->GetLocation()->GetSector() == Sector;
}

TSubclassOf<USelector> AItemPod::GetSelectorClass() const
{
	return SelectorClass.Get();
}
