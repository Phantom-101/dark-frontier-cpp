// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureProduction.h"
#include "Items/Inventory.h"
#include "Items/ItemStack.h"
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

	UInventory* Inventory = OwningPart->GetOwningStructure()->GetInventory();

	if(RequirementsMet)
	{
		// Recipe in progress
		
		Progress = FMath::Clamp(Progress + DeltaTime, 0, Recipe->Time);

		const bool CanFit = Inventory->CanFit(Recipe->Outputs->GetVolume(), Recipe->Outputs->GetMass());
		if(Progress == Recipe->Time && CanFit)
		{
			for(const FItemStack& Stack : Recipe->Outputs->GetStacks())
			{
				Inventory->AddItems(Stack.Item, Stack.Quantity);
			}
		}
	}
	else
	{
		// Recipe not in progress, try to start
		
		bool CanStartRecipe = true;
		// todo check faction wealth
		for(const FItemStack& Stack : Recipe->Inputs->GetStacks())
		{
			if(Inventory->GetItemQuantity(Stack.Item) < Stack.Quantity)
			{
				CanStartRecipe = false;
				break;
			}
		}

		if(CanStartRecipe)
		{
			for(const FItemStack& Stack : Recipe->Inputs->GetStacks())
			{
				Inventory->RemoveItems(Stack.Item, Stack.Quantity);
			}
			RequirementsMet = true;
		}
	}
}
