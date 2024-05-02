// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "StructureAbilityProxy.h"
#include "StructureTurretAbilityProxy.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureTurretAbilityProxy : public UStructureAbilityProxy
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructureTurret> Turret;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FGameplayAbilitySpecHandle AbilityHandle;

	virtual FGameplayAbilitySpecHandle GetAbilityHandle() override;

	virtual float GetArcLength() override;

};
