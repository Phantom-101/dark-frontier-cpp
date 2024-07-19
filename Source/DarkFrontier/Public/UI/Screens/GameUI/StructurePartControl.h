// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartControl.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructurePartControl : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual AStructurePart* GetPart();
	
};
