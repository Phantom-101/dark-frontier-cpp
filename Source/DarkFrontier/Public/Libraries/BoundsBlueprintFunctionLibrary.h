// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BoundsBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UBoundsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static FBoxSphereBounds GetBounds(const AActor* Actor, const bool OnlyCollidingComponents);

	UFUNCTION(BlueprintCallable)
	static FBoxSphereBounds GetActorBounds(const AActor* Actor, const bool OnlyCollidingComponents);

	UFUNCTION(BlueprintCallable)
	static FBoxSphereBounds GetStructureBounds(const class AStructure* Structure, const bool OnlyCollidingComponents);
	
};
