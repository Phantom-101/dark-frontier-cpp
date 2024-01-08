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

	UPROPERTY()
	TSubclassOf<class AStructurePart> PartClass;

	UPROPERTY()
	FText PartName;

	UFUNCTION()
	void Init(const AStructurePart* Part);
	
};
