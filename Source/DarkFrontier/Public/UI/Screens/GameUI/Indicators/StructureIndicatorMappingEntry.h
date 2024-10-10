// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndicatorMappingEntry.generated.h"

class UStructureIndicatorGroup;
class UStructureIndicator;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureIndicatorMappingEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UStructureIndicatorGroup> GroupClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UStructureIndicator> IndicatorClass;

	bool IsValid() const;
	
};
