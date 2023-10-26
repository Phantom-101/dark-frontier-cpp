// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartEntryObject.h"

void UCompatibleStructurePartEntryObject::Init(const AStructurePart* Part)
{
	PartClass = Part->GetClass();
	PartName = Part->TypeName;
}
