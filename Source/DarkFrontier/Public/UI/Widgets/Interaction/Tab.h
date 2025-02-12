// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Tab.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTab : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Name;

public:

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon();

	UFUNCTION(BlueprintCallable)
	FText GetName();
	
};
