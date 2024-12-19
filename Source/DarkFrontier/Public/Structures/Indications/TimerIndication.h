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
	FTimerHandle TimerHandle;

	void Init(FTimerHandle InHandle);

	float GetElapsedPercent() const;
	
};
