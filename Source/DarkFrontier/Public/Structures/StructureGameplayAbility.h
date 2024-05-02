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

protected:

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TObjectPtr<UTexture> Icon;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FText Description;

	/** Applied to cost effects in addition to effect magnitudes */
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TMap<FGameplayTag, float> CostMagnitudes;

	/** Applied to all outgoing gameplay effect specs, including cost effects */
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TMap<FGameplayTag, float> EffectMagnitudes;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpec(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const override;
	
};
