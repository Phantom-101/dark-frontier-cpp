// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureIndices.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"

UStructureIndices* UStructureIndices::CreateIndices(AStructure* Structure)
{
	UStructureIndices* Indices = Structure->CreateDefaultSubobject<UStructureIndices>("Indices");
	
	return Indices;
}

AStructure* UStructureIndices::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}

AStructurePart* UStructureIndices::GetRootPart() const
{
	return RootPart;
}

TArray<AStructurePart*> UStructureIndices::GetParts()
{
	return Parts;
}

AStructurePart* UStructureIndices::GetPart(const FString Id)
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

bool UStructureIndices::AddPart(AStructurePart* Part)
{
	if(Part->GetOwningStructure() == nullptr)
	{
		Parts.Add(Part);
		UpdateIndices();

		if(RootPart == nullptr)
		{
			RootPart = Part;
		}

		Part->OnAdded(GetStructure());

		return true;
	}

	return false;
}

bool UStructureIndices::RemovePart(AStructurePart* Part)
{
	if(Part->GetOwningStructure() == GetStructure() && Part != RootPart)
	{
		Parts.Remove(Part);
		UpdateIndices();

		Part->OnRemoved();

		return true;
	}

	return false;
}

void UStructureIndices::ReconnectParts()
{
	for(AStructurePart* Part : Parts)
	{
		Part->AttachSlots();
	}
}

void UStructureIndices::CullParts()
{
	TArray<AStructurePart*> ReachableParts;
	ReachableParts.Add(RootPart);

	int CurrentIndex = 0;
	while(CurrentIndex < ReachableParts.Num())
	{
		for(const UStructureSlot* Slot : ReachableParts[CurrentIndex]->GetSlots())
		{
			const UStructureSlot* Attached = Slot->GetAttachedSlot();
			if(Attached != nullptr && !ReachableParts.Contains(Attached->GetOwningPart()))
			{
				ReachableParts.Add(Attached->GetOwningPart());
			}
		}
		CurrentIndex++;
	}

	CurrentIndex = 0;
	while(CurrentIndex < Parts.Num())
	{
		if(!ReachableParts.Contains(Parts[CurrentIndex]))
		{
			RemovePart(Parts[CurrentIndex]);
			Parts[CurrentIndex]->Destroy();
		}
		else
		{
			CurrentIndex++;
		}
	}

	UpdateIndices();
}

TArray<UStructureSlot*> UStructureIndices::GetSlots()
{
	return Slots;
}

TArray<UStructureFacility*> UStructureIndices::GetFacilities()
{
	return Facilities;
}

void UStructureIndices::UpdateIndices()
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
