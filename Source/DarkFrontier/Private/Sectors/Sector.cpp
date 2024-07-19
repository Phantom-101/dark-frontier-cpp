// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/Sector.h"

ASector::ASector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASector::RegisterStructure(AStructure* Structure)
{
	Structures.Add(Structure);
}

void ASector::UnregisterStructure(AStructure* Structure)
{
	Structures.Remove(Structure);
}
