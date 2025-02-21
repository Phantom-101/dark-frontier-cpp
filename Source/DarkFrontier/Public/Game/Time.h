// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Time.generated.h"

struct FTimestamp;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FTime
{
	GENERATED_BODY()

	inline static float TimePerMinute = 1.0f;
	inline static float MinutesPerHour = 60.0f;
	inline static float HoursPerDay = 24.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Remainder;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Minutes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Hours;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Days;

	FTime();

	FTime(FTimestamp Timestamp);

	FTime Difference(FTime Other) const;

	FTimestamp ToTimestamp() const;

	FString ToString() const;
	
};
