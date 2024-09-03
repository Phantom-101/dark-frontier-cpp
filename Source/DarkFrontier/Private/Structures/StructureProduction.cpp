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
			const float TotalWeight = Recipe->Outputs->GetValue();

			if(TotalWeight == 0)
			{
				// Weights were not set, use quantities as weights
				const int TotalQuantity = Recipe->Outputs->GetQuantity();
					
				for(const FItemStack& Stack : Recipe->Outputs->GetStacks())
				{
					const float DistributedValue = InputValue * Stack.Quantity / TotalQuantity;
					Inventory->AddItems(Stack.Item, Stack.Quantity, DistributedValue);
				}
			}
			else
			{
				// Weights were set, assign values normally
				for(const FItemStack& Stack : Recipe->Outputs->GetStacks())
				{
					const float StackWeight = Stack.Value;
					const float DistributedValue = InputValue * StackWeight / TotalWeight;
					Inventory->AddItems(Stack.Item, Stack.Quantity, DistributedValue);
				}
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
			InputValue = 0;
			for(const FItemStack& Stack : Recipe->Inputs->GetStacks())
			{
				Inventory->RemoveItems(Stack.Item, Stack.Quantity, InputValue);
			}
			RequirementsMet = true;
		}
	}
}
