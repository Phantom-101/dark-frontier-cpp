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
	
	UPROPERTY(EditDefaultsOnly, Category="Costs")
	TMap<FGameplayTag, float> CostSetByCallerMagnitudes;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
};
