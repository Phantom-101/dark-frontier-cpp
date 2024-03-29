// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureLayoutPart.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureLayoutPart
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)	
	TSubclassOf<class AStructurePart> PartClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	int32 PartId = -1;

	FStructureLayoutPart();

	FStructureLayoutPart(const AStructurePart* InPart);
	
	bool IsValid() const;
	
};
