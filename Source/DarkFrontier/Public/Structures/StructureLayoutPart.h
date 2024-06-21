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
	TSubclassOf<class AStructurePart> PartType;

	/** If part id is null, it will be automatically generated when the layout is loaded. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	FString PartId;

	FStructureLayoutPart();

	FStructureLayoutPart(const AStructurePart* InPart);
	
	bool IsValid() const;
	
};
