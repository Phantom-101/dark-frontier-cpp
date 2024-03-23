// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartOptionObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartOptionObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TSubclassOf<class AStructurePart> PartClass;

	UFUNCTION()
	void Init(TSubclassOf<AStructurePart> InClass);
	
};
