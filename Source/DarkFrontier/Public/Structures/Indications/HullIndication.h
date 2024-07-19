// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.h"
#include "HullIndication.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHullIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float GetHullPercent() const;
	
};
