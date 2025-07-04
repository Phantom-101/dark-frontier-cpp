// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureProduction.h"
#include "Factions/Faction.h"
#include "Items/Recipe.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructurePart.h"

UStructureProduction::UStructureProduction()
{
	PrimaryComponentTick.bCanEverTick = true;
}

URecipe* UStructureProduction::GetRecipe() const
{
	return Recipe;
}

void UStructureProduction::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsValid(OwningPart) || !IsValid(Recipe)) return;

	UStructureInventory* Inventory = OwningPart->GetOwningStructure()->GetInventory();

	if(RequirementsMet)
	{
		// Recipe in progress
		Progress = FMath::Clamp(Progress + DeltaTime, 0, Recipe->Time);

		if(Progress == Recipe->Time && Inventory->FitsList(Recipe->Outputs))
		{
			Inventory->AddList(Recipe->Outputs);
			GetOwningStructure()->GetOwningFaction()->ChangeBalance(Recipe->Revenue);
			RequirementsMet = false;
			Progress = 0;
		}
	}
	else
	{
		// Recipe not in progress, try to start
		if(Inventory->HasList(Recipe->Inputs) && GetOwningStructure()->GetOwningFaction()->GetBalance() >= Recipe->Cost)
		{
			Inventory->RemoveList(Recipe->Inputs);
			GetOwningStructure()->GetOwningFaction()->ChangeBalance(-Recipe->Cost);
			RequirementsMet = true;
			Progress = 0;
		}
	}
}
