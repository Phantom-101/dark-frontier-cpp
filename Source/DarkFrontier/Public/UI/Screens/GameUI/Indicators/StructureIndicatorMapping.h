// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StructureIndicatorMapping.generated.h"

class UStructureIndicator;
class UStructureIndication;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureIndicatorMapping : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<UStructureIndication>, TSubclassOf<UStructureIndicator>> Mapping;

public:

	TSubclassOf<UStructureIndicator> Map(const TSubclassOf<UStructureIndication>& IndicationClass) const;

};
