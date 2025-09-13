// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructureFunctionLibrary.generated.h"

class AStructure;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static TArray<AStructure*> GetDockers(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	static AStructure* GetRoot(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	static TArray<AStructure*> GetInSubTree(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	static TArray<AStructure*> GetInTree(AStructure* Structure);
	
};
