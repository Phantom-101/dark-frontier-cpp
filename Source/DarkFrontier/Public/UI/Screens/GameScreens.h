﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameScreens.generated.h"

class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UGameScreens : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameStack;

public:

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidgetStack* GetGameStack() const;

protected:

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
};
