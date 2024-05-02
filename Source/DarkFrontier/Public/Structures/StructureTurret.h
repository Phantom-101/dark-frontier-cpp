// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Structures/StructurePart.h"
#include "StructureTurret.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AStructureTurret : public AStructurePart
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UStructureGameplayAbility> Ability;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle AbilityHandle;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;

	virtual void AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups) override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual float GetAbilityArcLength();
	
};
