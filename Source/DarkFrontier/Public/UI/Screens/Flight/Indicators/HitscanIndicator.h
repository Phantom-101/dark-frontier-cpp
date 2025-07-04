// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndicator.h"
#include "HitscanIndicator.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UHitscanIndicator : public UStructureIndicator
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class USizeBox> SizeBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxSize = 100;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
