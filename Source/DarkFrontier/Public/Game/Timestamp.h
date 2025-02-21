// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Timestamp.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FTimestamp
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;

	FTimestamp();

	FTimestamp(float InValue);

	FTimestamp Difference(FTimestamp Other) const;
	
};
