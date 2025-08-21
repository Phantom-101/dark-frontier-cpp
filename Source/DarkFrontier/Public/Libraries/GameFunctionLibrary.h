// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFunctionLibrary.generated.h"

class AStructure;
class AStructureController;
/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static AStructureController* GetPlayerController(const UObject* WorldContext);

	UFUNCTION(BlueprintPure)
	static AStructure* GetPlayerStructure(const UObject* WorldContext);
	
};
