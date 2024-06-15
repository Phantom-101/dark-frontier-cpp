// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Turret")
	TArray<TObjectPtr<class UFiringPoint>> FiringPoints;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UStructureAbility> AbilityClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag PayloadEventTag;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle AbilityHandle;

	virtual void BeginPlay() override;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual struct FStructureDamage GetDamage();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void ActivateAll();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void OnActivatedAll();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void Activate(UFiringPoint* FiringPoint);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void OnActivated(UFiringPoint* FiringPoint);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void SendPayload(UObject* PayloadObject);

	virtual void AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups) override;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void TryActivate();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual float GetAbilityArcLength();
	
};
