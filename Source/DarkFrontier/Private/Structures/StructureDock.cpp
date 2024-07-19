// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDock.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"

void UStructureDock::BeginPlay()
{
	Super::BeginPlay();

	OwningPart = Cast<AStructurePart>(GetOwner());
}

AStructure* UStructureDock::GetOwningStructure() const
{
	return OwningPart->GetOwningStructure();
}

AStructurePart* UStructureDock::GetOwningPart() const
{
	return OwningPart;
}

bool UStructureDock::TryDock(AStructure* Structure)
{
	if(IsValid(Docker) || !IsValid(Structure) || IsValid(Structure->GetDock())) return false;

	Docker = Structure;
	Docker->DockAt(this);
	
	return true;
}

bool UStructureDock::TryUnDock()
{
	if(!IsValid(Docker)) return false;

	Docker->UnDock();
	Docker = nullptr;

	return true;
}
