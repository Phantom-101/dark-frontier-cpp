// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartAbilityClass.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartAbilityClass : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructure> TargetStructure;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSubclassOf<class AStructurePart> PartClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSubclassOf<class UStructureGameplayAbility> AbilityClass;
	
};
