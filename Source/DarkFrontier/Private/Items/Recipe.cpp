// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Recipe.h"
#include "Items/ItemList.h"

URecipe::URecipe()
{
	Inputs = CreateDefaultSubobject<UItemList>("Inputs");
	Outputs = CreateDefaultSubobject<UItemList>("Outputs");
}
