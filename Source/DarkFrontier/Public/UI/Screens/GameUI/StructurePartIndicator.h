// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartIndicator.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructurePartIndicator : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual AStructurePart* GetPart();
	
};
