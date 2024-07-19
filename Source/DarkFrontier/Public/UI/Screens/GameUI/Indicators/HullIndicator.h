// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndicator.h"
#include "HullIndicator.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UHullIndicator : public UStructureIndicator
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCurveLinearColor> ColorCurve;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
