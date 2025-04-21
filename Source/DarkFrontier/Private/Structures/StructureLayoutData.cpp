// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayoutData.h"
#include "Log.h"
#include "Structures/Structure.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"

FStructureLayoutData::FStructureLayoutData()
{
}

FStructureLayoutData::FStructureLayoutData(const AStructure* InStructure)
{
	AStructurePart* Root = InStructure->GetLayout()->GetRootPart();
	if(!IsValid(Root))
	{
		UE_LOG(LogDarkFrontier, Error, TEXT("Structure has invalid root part"));
		return;
	}
	
	TQueue<AStructurePart*> Queue;
	TSet<AStructurePart*> Visited;
	Queue.Enqueue(Root);
	Visited.Add(Root);

	AStructurePart* Current;
	while(!Queue.IsEmpty())
	{
		Queue.Dequeue(Current);

		Parts.Add(FStructureLayoutPart(Current));

		for(const UStructureSlot* PartSlot : Current->GetSlots())
		{
			if(IsValid(PartSlot->GetAttachedSlot()))
			{
				AStructurePart* Other = PartSlot->GetAttachedSlot()->GetOwningPart();
				if(IsValid(Other) && !Visited.Contains(Other))
				{
					Queue.Enqueue(Other);
					Visited.Add(Other);

					Connections.Add(FStructureLayoutConnection(PartSlot, PartSlot->GetAttachedSlot()));
				}
			}
		}
	}
}
