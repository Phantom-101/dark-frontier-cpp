// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "AlternatingColorScope.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UAlternatingColorScope : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	// Use FLinearColor as FColors are converted into a different color space when foreground color is set
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLinearColor> Colors;

protected:

	// Cannot use NativeConstruct or NativeOnInitialized as the slate hierarchy has not been initialized
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
