// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructureGameplayAbility.h"
#include "StructureTurretAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureTurretAbility : public UStructureGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag EventTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UStructureDamageTags> DamageTags;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	TObjectPtr<class UAbilityTask_WaitGameplayEvent> WaitEventTask;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void HandleEventDataReceived(FGameplayEventData Payload);
	
};
