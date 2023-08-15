// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructureSection.h"
#include "CompatibleSectionEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCompatibleSectionEntryObject : public UObject
{
	GENERATED_BODY()

public:

	TSubclassOf<class AStructureSection> SectionType;
	
	void Init(const AStructureSection* Section);
	
};
