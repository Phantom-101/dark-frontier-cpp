// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructurePartControlsMapping.generated.h"

class UStructurePartControls;
class AStructurePart;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartControlsMapping : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<AStructurePart>, TSubclassOf<UStructurePartControls>> Mapping;

public:

	TSubclassOf<UStructurePartControls> Map(const TSubclassOf<AStructurePart>& PartClass) const;
	
};
