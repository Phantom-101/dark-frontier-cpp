// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "GameplaySubobject.generated.h"

class UStructureAbilitySystemComponent;
class UGameplayEffect;
class UStructureAbility;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UGameplaySubobject : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Initialize() const;

	UFUNCTION(BlueprintCallable)
	AActor* GetActor() const;

	UFUNCTION(BlueprintCallable)
	virtual UStructureAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable)
	FActiveGameplayEffectHandle ApplyEffect(TSubclassOf<UGameplayEffect> Effect) const;

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(FActiveGameplayEffectHandle Handle) const;

	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GiveAbility(TSubclassOf<UStructureAbility> Ability) const;

	UFUNCTION(BlueprintCallable)
	void ClearAbility(FGameplayAbilitySpecHandle Handle) const;
	
};
