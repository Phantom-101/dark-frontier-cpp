// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "StructureDamage.h"
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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FStructureDamage BaseDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	bool RequiresAmmo = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TArray<TObjectPtr<class UAmmo>> AmmoTypes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	float AmmoDamageMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	float Cooldown = 10;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Setup")
	TArray<TObjectPtr<class UFiringPoint>> FiringPoints;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UStructureGameplayAbility> TurretAbilityClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle TurretAbilityHandle;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;

	virtual void AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups) override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual float GetAbilityArcLength();
	
};
