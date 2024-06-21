// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureSlotFilter.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UStructureSlotFilter : public UObject
{
	GENERATED_BODY()

public:

	virtual bool IsCompatible(const class UStructureSlot* Other);
	
};
