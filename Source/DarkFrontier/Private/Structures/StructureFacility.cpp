// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureFacility.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Items/Recipe.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"

UStructureFacility::UStructureFacility()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStructureFacility::BeginPlay()
{
	Super::BeginPlay();

	OwningPart = Cast<AStructurePart>(GetOwner());
}

void UStructureFacility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsValid(OwningPart) || !IsValid(CurrentRecipe)) return;

	UInventory* Inventory = OwningPart->GetOwningStructure()->GetInventory();

	if(RequirementsMet)
	{
		// Recipe in progress
		
		Progress = FMath::Clamp(Progress + DeltaTime, 0, CurrentRecipe->Time);

		const bool CanFit = Inventory->CanFit(CurrentRecipe->Outputs->GetVolume(), CurrentRecipe->Outputs->GetMass());
		if(Progress == CurrentRecipe->Time && CanFit)
		{
			const float TotalWeight = CurrentRecipe->Outputs->GetValue();

			if(TotalWeight == 0)
			{
				// Weights were not set, use quantities as weights
				const int TotalQuantity = CurrentRecipe->Outputs->GetQuantity();
					
				for(const FItemStack& Stack : CurrentRecipe->Outputs->GetStacks())
				{
					const float DistributedValue = InputValue * Stack.Quantity / TotalQuantity;
					Inventory->AddItems(Stack.Item, Stack.Quantity, DistributedValue);
				}
			}
			else
			{
				// Weights were set, assign values normally
				for(const FItemStack& Stack : CurrentRecipe->Outputs->GetStacks())
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
		// Recipe not in progress, try to find a recipe to start
		
		bool CanStartRecipe = true;
		// todo check faction wealth
		for(const FItemStack& Stack : CurrentRecipe->Inputs->GetStacks())
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
			for(const FItemStack& Stack : CurrentRecipe->Inputs->GetStacks())
			{
				Inventory->RemoveItems(Stack.Item, Stack.Quantity, InputValue);
			}
			RequirementsMet = true;
		}
	}
}

AStructure* UStructureFacility::GetOwningStructure() const
{
	return OwningPart->GetOwningStructure();
}

AStructurePart* UStructureFacility::GetOwningPart() const
{
	return OwningPart;
}
