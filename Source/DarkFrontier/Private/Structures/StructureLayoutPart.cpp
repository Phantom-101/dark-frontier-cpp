// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureLayoutPart.h"
#include "Structures/StructurePart.h"

FStructureLayoutPart::FStructureLayoutPart()
{
}

FStructureLayoutPart::FStructureLayoutPart(const AStructurePart* InPart)
{
	PartClass = InPart->GetClass();
	PartId = InPart->GetPartId();
}

bool FStructureLayoutPart::IsValid() const
{
	return PartClass != nullptr && PartId >= 0;
}
