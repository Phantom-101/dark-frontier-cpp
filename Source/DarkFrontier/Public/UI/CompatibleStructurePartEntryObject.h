// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePart.h"
#include "CompatibleStructurePartEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCompatibleStructurePartEntryObject : public UObject
{
	GENERATED_BODY()

public:

	TSubclassOf<class AStructurePart> PartClass;
	
	void Init(const AStructurePart* Part);
	
};
