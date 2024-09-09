// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "StructureGameplay.generated.h"

class UStructureAbility;
class UStructureAttributeSet;
class UStructureAbilitySystemComponent;
class UGameplayEffect;
class AStructure;

/**
 * 
 */
UCLASS(DefaultToInstanced)
class DARKFRONTIER_API UStructureGameplay : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> StartingEffects;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureAttributeSet> AttributeSet;

public:

	static UStructureGameplay* CreateGameplay(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	void Initialize() const;

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;
	
	UFUNCTION(BlueprintCallable)
	UStructureAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable)
	UStructureAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHull() const;

	UFUNCTION(BlueprintCallable)
	float GetHull() const;

	UFUNCTION(BlueprintCallable)
	void SetHull(float InHull) const;

	UFUNCTION(BlueprintCallable)
	float GetMaxShield() const;

	UFUNCTION(BlueprintCallable)
	float GetShield() const;

	UFUNCTION(BlueprintCallable)
	void SetShield(float InShield) const;

	UFUNCTION(BlueprintCallable)
	float GetMaxEnergy() const;
	
	UFUNCTION(BlueprintCallable)
	float GetEnergy() const;
	
	UFUNCTION(BlueprintCallable)
	float GetUpkeep() const;

	UFUNCTION(BlueprintCallable)
	float GetLinearMaxSpeed() const;
	
	UFUNCTION(BlueprintCallable)
	float GetLinearSpeed() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsDetecting(AStructure* Other) const;

	UFUNCTION(BlueprintCallable)
	void ApplyStartingEffects();

	UFUNCTION(BlueprintCallable)
	FActiveGameplayEffectHandle ApplyEffect(TSubclassOf<UGameplayEffect> Effect) const;

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(FActiveGameplayEffectHandle Handle) const;

	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GiveAbility(TSubclassOf<UStructureAbility> Ability) const;

	UFUNCTION(BlueprintCallable)
	void ClearAbility(FGameplayAbilitySpecHandle Handle) const;
	
};
