// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureFacility.h"
#include "Structures/StructurePart.h"

void UStructureFacility::BeginPlay()
{
	Super::BeginPlay();

	OwningPart = GetOwner<AStructurePart>();
}

AStructure* UStructureFacility::GetOwningStructure() const
{
	return OwningPart->GetOwningStructure();
}

AStructurePart* UStructureFacility::GetOwningPart() const
{
	return OwningPart;
}
