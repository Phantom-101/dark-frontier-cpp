// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartClass.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartClass : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> TargetStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSubclassOf<AStructurePart> PartClass;
	
};
