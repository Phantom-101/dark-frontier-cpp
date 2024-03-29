// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureAuthoring.h"
#include "Structures/Structure.h"

void UStructureAuthoring::BeginPlay()
{
	Super::BeginPlay();

	AStructure* Structure = Cast<AStructure>(GetOwner());
	if(IsValid(Structure))
	{
		Structure->LoadLayout(Layout);
	}
}
