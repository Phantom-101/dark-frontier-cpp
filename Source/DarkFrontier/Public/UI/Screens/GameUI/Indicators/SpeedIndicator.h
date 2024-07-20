// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndicator.h"
#include "SpeedIndicator.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API USpeedIndicator : public UStructureIndicator
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> SpeedText;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
