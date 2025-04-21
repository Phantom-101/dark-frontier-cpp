// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayout.h"

#include "Log.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayoutData.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"

UStructureLayout* UStructureLayout::CreateLayout(AStructure* Structure)
{
	UStructureLayout* Layout = Structure->CreateDefaultSubobject<UStructureLayout>("Layout");
	
	return Layout;
}

AStructure* UStructureLayout::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}

AStructurePart* UStructureLayout::GetRootPart() const
{
	return RootPart;
}

TArray<AStructurePart*> UStructureLayout::GetParts()
{
	return Parts;
}

AStructurePart* UStructureLayout::GetPart(const FString Id)
{
	for(AStructurePart* Part : Parts)
	{
		if(Part->GetPartId().Equals(Id))
		{
			return Part;
		}
	}
	return nullptr;
}

bool UStructureLayout::AddPart(AStructurePart* Part)
{
	if(Part->GetOwningStructure() == nullptr)
	{
		Parts.Add(Part);
		UpdateLayout();

		if(!::IsValid(RootPart))
		{
			RootPart = Part;
		}

		Part->OnAdded(GetStructure());

		return true;
	}

	return false;
}

bool UStructureLayout::RemovePart(AStructurePart* Part)
{
	if(Part->GetOwningStructure() == GetStructure() && Part != RootPart)
	{
		Parts.Remove(Part);
		UpdateLayout();

		Part->OnRemoved();
		Part->Destroy();

		return true;
	}

	return false;
}

void UStructureLayout::RemoveAll()
{
	for(AStructurePart* Part : Parts)
	{
		Part->OnRemoved();
		Part->Destroy();
	}

	RootPart = nullptr;
	Parts.Empty();
	UpdateLayout();
}

void UStructureLayout::ConnectAll()
{
	for(AStructurePart* Part : Parts)
	{
		Part->AttachSlots();
	}
}

TArray<AStructurePart*> UStructureLayout::GetConnected() const
{
	TArray<AStructurePart*> Connected;
	Connected.Add(RootPart);

	for(int Index = 0; Index < Connected.Num(); Index++)
	{
		for(const UStructureSlot* Slot : Connected[Index]->GetSlots())
		{
			const UStructureSlot* Attached = Slot->GetAttachedSlot();
			if(Attached != nullptr && !Connected.Contains(Attached->GetOwningPart()))
			{
				Connected.Add(Attached->GetOwningPart());
			}
		}
	}
	
	return Connected;
}

TArray<AStructurePart*> UStructureLayout::GetDisconnected() const
{
	const TArray<AStructurePart*> Connected = GetConnected();
	TArray<AStructurePart*> Disconnected;

	for(AStructurePart* Part : Parts)
	{
		if(!Connected.Contains(Part))
		{
			Disconnected.Add(Part);
		}
	}

	return Disconnected;
}

void UStructureLayout::RemoveUnconnected()
{
	for(AStructurePart* Part : GetDisconnected())
	{
		RemovePart(Part);
	}
	
	UpdateLayout();
}

TArray<UStructureSlot*> UStructureLayout::GetSlots()
{
	return Slots;
}

TArray<UStructureFacility*> UStructureLayout::GetFacilities()
{
	return Facilities;
}

bool UStructureLayout::IsValid()
{
	if(!::IsValid(RootPart))
	{
		return false;
	}
	
	for(int i = 0; i < Parts.Num(); i++)
	{
		for(int j = i + 1; j < Parts.Num(); j++)
		{
			if(Parts[i]->IsOverlappingActor(Parts[j]))
			{
				return false;
			}
		}
	}
	
	if(GetStructure()->GetGameplay()->GetUpkeep() > GetStructure()->GetGameplay()->GetMaxUpkeep())
	{
		return false;
	}

	return true;
}

bool UStructureLayout::LoadData(FStructureLayoutData Data)
{
	RemoveAll();

	// If any layout part has an empty id, set it to a random guid
	for(int i = 0; i < Data.Parts.Num(); i++)
	{
		if(Data.Parts[i].PartId.IsEmpty())
		{
			Data.Parts[i].PartId = FGuid::NewGuid().ToString();
		}
	}
	
	for(FStructureLayoutPart PartData : Data.Parts)
	{
		if(!PartData.IsValid())
		{
			// Layout part ids already randomized if empty at this point
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout part on %s with invalid class"), *GetName());
			continue;
		}
		
		AStructurePart* Part = GetWorld()->SpawnActor<AStructurePart>(PartData.PartType);
		Part->TryInitPartId(PartData.PartId);
		// First part will automatically be set as the root part
		AddPart(Part);
	}

	if(!::IsValid(RootPart)) return false;

	for(FStructureLayoutConnection ConnectionData : Data.Connections)
	{
		if(!ConnectionData.IsValid())
		{
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with unset ids"), *GetName());
			continue;
		}

		AStructurePart* PartA = GetPart(ConnectionData.PartAId);
		AStructurePart* PartB = GetPart(ConnectionData.PartBId);

		if(!::IsValid(PartA) || !::IsValid(PartB))
		{
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with missing/invalid part(s)"), *GetName());
			continue;
		}

		UStructureSlot* SlotA = PartA->GetSlot(ConnectionData.PartASlot);
		UStructureSlot* SlotB = PartB->GetSlot(ConnectionData.PartBSlot);

		if(!::IsValid(SlotA) || !::IsValid(SlotB))
		{
			UE_LOG(LogDarkFrontier, Warning, TEXT("Invalid layout connection on %s with missing/invalid slots(s)"), *GetName());
			continue;
		}

		if(!SlotA->TryAttach(SlotB))
		{
			UE_LOG(LogDarkFrontier, Warning, TEXT("Failed to create layout connection on %s between %s (%s), %s (%s)"), *GetName(), *ConnectionData.PartAId, *ConnectionData.PartASlot.ToString(), *ConnectionData.PartBId, *ConnectionData.PartBSlot.ToString());
		}
	}

	ConnectAll();

	return true;
}

void UStructureLayout::UpdateLayout()
{
	Slots.Empty();
	Facilities.Empty();
	for(AStructurePart* Part : Parts)
	{
		Slots.Append(Part->GetSlots());
		Facilities.Append(Part->GetFacilities());
	}

	OnUpdated.Broadcast();
}
