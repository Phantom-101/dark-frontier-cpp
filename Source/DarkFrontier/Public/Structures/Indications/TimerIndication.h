// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.h"
#include "TimerIndication.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTimerIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float StartTime = 0;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float Duration = 0;

	void Init(float InDuration);

	float GetElapsedPercent() const;
	
};
