// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.h"
#include "ShieldIndication.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UShieldIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float GetShieldPercent() const;
	
};
