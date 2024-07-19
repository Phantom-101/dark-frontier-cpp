// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructureIndication.h"
#include "HitscanIndication.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHitscanIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float MaxTime = 0;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float CurrentTime = 0;

};
