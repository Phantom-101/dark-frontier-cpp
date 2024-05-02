// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructureDamageTags.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UStructureDamageTags : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FGameplayTag KineticTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FGameplayTag ExplosiveTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FGameplayTag BeamTag;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	FGameplayTag FieldTag;

};
