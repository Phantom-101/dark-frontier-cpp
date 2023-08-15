// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureSectionSlotType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UStructureSectionSlotType : public UObject
{
	GENERATED_BODY()

public:

	UStructureSectionSlotType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanAttach(UStructureSectionSlotType* Other);
	
};
