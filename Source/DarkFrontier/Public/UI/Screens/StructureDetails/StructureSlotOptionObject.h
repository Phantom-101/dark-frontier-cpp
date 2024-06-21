// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureSlotOptionObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotOptionObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FText SlotName;
	
};
