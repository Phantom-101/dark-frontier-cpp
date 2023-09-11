// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompatibleStructurePartSlotEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCompatibleStructurePartSlotEntryObject : public UObject
{
	GENERATED_BODY()

public:

	TSubclassOf<class AStructurePart> PartClass;

	FText SlotName;
	
	void Init(const class UStructurePartSlot* PartSlot);
	
};
