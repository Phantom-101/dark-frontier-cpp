// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleSectionEntryObject.h"

void UCompatibleSectionEntryObject::Init(const AStructureSection* Section)
{
	SectionType = Section->GetClass();
}
