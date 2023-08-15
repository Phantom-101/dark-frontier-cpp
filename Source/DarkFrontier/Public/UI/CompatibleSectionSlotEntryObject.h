// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompatibleSectionSlotEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCompatibleSectionSlotEntryObject : public UObject
{
	GENERATED_BODY()

public:

	TSubclassOf<class AStructureSection> SectionType;

	FText SlotName;
	
	void Init(const class UStructureSectionSlot* SectionSlot);
	
};
