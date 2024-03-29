// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartAuthoring.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

UStructurePartAuthoring::UStructurePartAuthoring()
{
}

void UStructurePartAuthoring::BeginPlay()
{
	Super::BeginPlay();

	GetAuthoredPart();
}

AStructurePart* UStructurePartAuthoring::GetAuthoredPart()
{
	if(!AuthoredPart)
	{
		AuthoredPart = GetWorld()->SpawnActor<AStructurePart>(PartClass);
		
		if(TargetPart)
		{
			AuthoredPart->GetSlot(UseSlot)->TryAttach(TargetPart->GetAuthoredPart()->GetSlot(TargetSlot));
		}
		else
		{
			Cast<AStructure>(GetOwner())->TryInit(AuthoredPart);
		}

		DestroyComponent();
	}

	return AuthoredPart;
}
