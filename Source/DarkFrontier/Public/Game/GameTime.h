// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameTime.generated.h"

class UGameTimestamp;

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UGameTime : public UObject
{
	GENERATED_BODY()

public:
	
	inline static float FractionalPerMinute = 1.0f;
	inline static float MinutesPerHour = 60.0f;
	inline static float HoursPerDay = 24.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Fractional = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Minutes = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Hours = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Days = 0;

	static UGameTime* FromTimestamp(const UGameTimestamp* Timestamp);

	UGameTimestamp* ToTimestamp() const;
	
};
