// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Screens.generated.h"

class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UScreens : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Stack;

public:

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidgetStack* GetStack() const;

protected:

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
};
