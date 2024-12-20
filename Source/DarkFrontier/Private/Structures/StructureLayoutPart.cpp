// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayoutPart.h"
#include "Structures/StructurePart.h"

FStructureLayoutPart::FStructureLayoutPart()
{
}

FStructureLayoutPart::FStructureLayoutPart(const AStructurePart* InPart)
{
	PartType = InPart->GetClass();
	PartId = InPart->GetPartId();
}

bool FStructureLayoutPart::IsValid() const
{
	return PartType != nullptr && !PartId.IsEmpty();
}
