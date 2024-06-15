// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartSlotOptionObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartSlotOptionObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FText SlotName;
	
};
