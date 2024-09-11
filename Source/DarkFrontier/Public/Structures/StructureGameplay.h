// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "StructureGameplay.generated.h"

class UShieldAttributeSet;
class USignatureAttributeSet;
class ULayoutAttributeSet;
class UEnergyAttributeSet;
class UResistanceAttributeSet;
class UIntegrityAttributeSet;
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

	// TODO replace with wrapper classes
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UIntegrityAttributeSet> IntegrityAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UResistanceAttributeSet> ResistanceAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UShieldAttributeSet> ShieldAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UEnergyAttributeSet> EnergyAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ULayoutAttributeSet> LayoutAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<USignatureAttributeSet> SignatureAttributes;

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
	UIntegrityAttributeSet* GetIntegrityAttributes() const;

	UFUNCTION(BlueprintCallable)
	UResistanceAttributeSet* GetResistanceAttributes() const;

	UFUNCTION(BlueprintCallable)
	UShieldAttributeSet* GetShieldAttributes() const;

	UFUNCTION(BlueprintCallable)
	UEnergyAttributeSet* GetEnergyAttributes() const;
	
	UFUNCTION(BlueprintCallable)
	ULayoutAttributeSet* GetLayoutAttributes() const;

	UFUNCTION(BlueprintCallable)
	USignatureAttributeSet* GetSignatureAttributes() const;

	// TODO replace with smaller attribute sets
	UFUNCTION(BlueprintCallable)
	UStructureAttributeSet* GetStructureAttributes() const;

	// TODO move out
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
