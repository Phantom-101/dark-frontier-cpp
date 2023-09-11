// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartSlotType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UStructurePartSlotType : public UObject
{
	GENERATED_BODY()

public:

	UStructurePartSlotType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanAttach(UStructurePartSlotType* Other);
	
};
