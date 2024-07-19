// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Recipe.h"
#include "Items/Inventory.h"

URecipe::URecipe()
{
	Inputs = CreateDefaultSubobject<UInventory>("Inputs");
	Outputs = CreateDefaultSubobject<UInventory>("Outputs");
}
