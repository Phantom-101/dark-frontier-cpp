// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "AnnotatedArc.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UAnnotatedArc : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UArc> Arc;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UNamedSlot> ContentSlot;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Size = 1000;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Thickness = 10;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Direction = 0.25;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Gap = 0.05;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor Color;

	virtual void NativePreConstruct() override;
	
};
