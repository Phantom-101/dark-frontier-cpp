// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	FStructureDamage BaseDamage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	float Cooldown = 10;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	bool RequiresAmmo = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	float AmmoDamageMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	TArray<TObjectPtr<class UAmmo>> AmmoTypes;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Turret")
	TObjectPtr<UAmmo> CurrentAmmoType;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Turret")
	TArray<TObjectPtr<class UFiringPoint>> FiringPoints;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UStructureGameplayAbility> TurretAbilityClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag EventTag;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle TurretAbilityHandle;

	virtual void BeginPlay() override;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;
	
	UFUNCTION(BlueprintCallable, Category="Turret")
	FStructureDamage GetDamage() const;

	UFUNCTION(BlueprintCallable, Category="Turret")
	float GetCooldown() const;

	UFUNCTION(BlueprintCallable, Category="Turret")
	TArray<UAmmo*> GetAmmoTypes();

	UFUNCTION(BlueprintCallable, Category="Turret")
	UAmmo* GetCurrentAmmoType() const;

	UFUNCTION(BlueprintCallable, Category="Turret")
	bool TrySetCurrentAmmoType(UAmmo* AmmoType);

	virtual void AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups) override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void TryActivate();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual float GetAbilityArcLength();
	
};
