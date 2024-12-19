// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartControls.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructurePartControls : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> Part;

public:

	UFUNCTION(BlueprintCallable)
	virtual bool TryInitialize(AStructurePart* InPart);

	UFUNCTION(BlueprintCallable)
	virtual AStructurePart* GetPart();
	
};
