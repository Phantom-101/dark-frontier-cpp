// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePart.h"
#include "Structures/Structure.h"
#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePartSlotType.h"

AStructurePart::AStructurePart()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStructurePart::BeginPlay()
{
	Super::BeginPlay();
}

void AStructurePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// stuff here
}

void AStructurePart::InitOwningStructure(AStructure* NewOwner)
{
	OwningStructure = NewOwner;
	OwningStructure->RegisterPart(this);
	AttachToActor(OwningStructure, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
}

void AStructurePart::RegisterPartSlot(UStructurePartSlot* Slot)
{
	PartSlots.Add(Slot);
}

UStructurePartSlot* AStructurePart::GetPartSlotByName(const FText Name)
{
	for(UStructurePartSlot* Slot : PartSlots)
	{
		if(Slot->SlotName.EqualToCaseIgnored(Name))
		{
			return Slot;
		}
	}
	
	return nullptr;
}

TArray<UStructurePartSlot*> AStructurePart::GetCompatiblePartSlots(const TSubclassOf<UStructurePartSlotType> SlotType)
{
	TArray<UStructurePartSlot*> Ret;
	for(UStructurePartSlot* Slot : PartSlots)
	{
		if(Slot->SlotType.GetDefaultObject()->CanAttach(SlotType.GetDefaultObject()))
		{
			Ret.Add(Slot);
		}
	}
	return Ret;
}

void AStructurePart::AttachNearbyPartSlots()
{
	for(UStructurePartSlot* Slot : PartSlots)
	{
		if(Slot->AttachedSlot == nullptr)
		{
			for(AStructurePart* Part : OwningStructure->GetCachedParts())
			{
				if(Part != this)
				{
					for(UStructurePartSlot* Candidate : Part->PartSlots)
					{
						if((Candidate->GetComponentLocation() - Slot->GetComponentLocation()).IsNearlyZero(1))
						{
							Slot->Attach(Candidate);
						}
					}
				}
			}
		}
	}
}

void AStructurePart::RemovePart()
{
	if(OwningStructure->GetRootPart() != this)
	{
		for(UStructurePartSlot* Slot : PartSlots)
		{
			Slot->Detach();
		}
		OwningStructure->UpdateCachedParts();
	}
}
