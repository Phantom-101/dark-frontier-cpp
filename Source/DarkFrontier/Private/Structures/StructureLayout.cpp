// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayout.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

FStructureLayout::FStructureLayout()
{
}

FStructureLayout::FStructureLayout(const AStructure* InStructure)
{
	TQueue<AStructurePart*> Queue;
	const TSet<AStructurePart*> Visited;
	Queue.Enqueue(InStructure->GetRootPart());

	AStructurePart* Current;
	while(!Queue.IsEmpty())
	{
		Queue.Dequeue(Current);

		Parts.Add(FStructureLayoutPart(Current));

		for(const UStructurePartSlot* PartSlot : Current->GetSlots())
		{
			if(IsValid(PartSlot->GetAttachedSlot()))
			{
				AStructurePart* Other = PartSlot->GetAttachedSlot()->GetOwningPart();
				if(IsValid(Other) && !Visited.Contains(Other))
				{
					Queue.Enqueue(Other);

					Connections.Add(FStructureLayoutConnection(PartSlot, PartSlot->GetAttachedSlot()));
				}
			}
		}
	}
}
