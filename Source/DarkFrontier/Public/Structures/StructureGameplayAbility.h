// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "StructureGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UStructureGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 InputID;
	
};
