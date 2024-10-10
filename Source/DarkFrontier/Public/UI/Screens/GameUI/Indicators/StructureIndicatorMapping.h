// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndicatorMappingEntry.h"
#include "UObject/Object.h"
#include "StructureIndicatorMapping.generated.h"

class UStructureIndication;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class DARKFRONTIER_API UStructureIndicatorMapping : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FStructureIndicatorMappingEntry DefaultEntry;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<UStructureIndication>, FStructureIndicatorMappingEntry> Entries;

public:

	FStructureIndicatorMappingEntry Find(const TSubclassOf<UStructureIndication>& IndicationClass);

	FStructureIndicatorMappingEntry Find(const UStructureIndication* Indication);
	
};
