// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartOptionObject.h"

void UStructurePartOptionObject::Init(const TSubclassOf<AStructurePart> InClass)
{
	PartClass = InClass;
}
