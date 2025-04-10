// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UViewTarget : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual bool IsValid();
	
	UFUNCTION(BlueprintCallable)
	virtual FVector GetViewLocation();

	UFUNCTION(BlueprintCallable)
	virtual FRotator GetViewRotation();

	UFUNCTION(BlueprintCallable)
	virtual double GetViewDistance();
	
};
