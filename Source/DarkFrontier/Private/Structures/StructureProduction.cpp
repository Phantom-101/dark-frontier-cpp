// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureProduction.h"
#include "Items/Inventory.h"
#include "Items/Recipe.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"

UStructureProduction::UStructureProduction()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStructureProduction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsValid(OwningPart) || !IsValid(Recipe)) return;

	const UInventory* Inventory = OwningPart->GetOwningStructure()->GetInventory();

	if(RequirementsMet)
	{
		// Recipe in progress
		
		Progress = FMath::Clamp(Progress + DeltaTime, 0, Recipe->Time);

		if(Progress == Recipe->Time && Inventory->FitsList(Recipe->Outputs))
		{
			Inventory->AddList(Recipe->Outputs);
			RequirementsMet = false;
			Progress = 0;
		}
	}
	else
	{
		// Recipe not in progress, try to start
		
		// todo check faction wealth

		if(Inventory->HasList(Recipe->Inputs))
		{
			Inventory->RemoveList(Recipe->Inputs);
			RequirementsMet = true;
			Progress = 0;
		}
	}
}
