// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureAbilityProxyGroup.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureAbilityProxyGroup : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TSubclassOf<class UStructureAbility> AbilityClass;

	UPROPERTY()
	TObjectPtr<class AStructure> TargetStructure;

	UPROPERTY()
	TArray<TObjectPtr<class UStructureAbilityProxy>> Proxies;
	
};
