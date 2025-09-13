// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/StructureFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"
#include "Structures/StructureLayout.h"

TArray<AStructure*> UStructureFunctionLibrary::GetDockers(AStructure* Structure)
{
	TArray<AStructure*> Dockers;
	for(const UStructureDock* Dock : Structure->GetLayout()->GetFacilities<UStructureDock>())
	{
		if(IsValid(Dock->GetDocker()))
		{
			Dockers.Add(Dock->GetDocker());
		}
	}
	return Dockers;
}

AStructure* UStructureFunctionLibrary::GetRoot(AStructure* Structure)
{
	AStructure* Root = Structure;
	while(Root->GetDockable()->GetDockStructure() != nullptr)
	{
		Root = Root->GetDockable()->GetDockStructure();
	}
	return Root;
}

TArray<AStructure*> UStructureFunctionLibrary::GetInSubTree(AStructure* Structure)
{
	TArray<AStructure*> Structures;
	Structures.Add(Structure);

	int Index = 0;
	while(Index < Structures.Num())
	{
		Structures.Append(GetDockers(Structures[Index]));
		Index++;
	}

	return Structures;
}

TArray<AStructure*> UStructureFunctionLibrary::GetInTree(AStructure* Structure)
{
	return GetInSubTree(GetRoot(Structure));
}
