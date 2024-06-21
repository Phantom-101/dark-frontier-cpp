// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructureSlotType.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotType : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText TypeName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor Color;
	
};
