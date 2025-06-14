// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "AlternateColor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UAlternateColor : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	// Use FLinearColor as FColors are converted into a different color space when foreground color is set
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLinearColor> Colors;

protected:

	virtual void NativeOnInitialized() override;

};
