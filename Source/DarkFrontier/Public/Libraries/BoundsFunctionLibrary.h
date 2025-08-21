// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BoundsFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UBoundsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static FBoxSphereBounds GetLocalBounds(const AActor* Actor, const bool OnlyCollidingComponents);

};
