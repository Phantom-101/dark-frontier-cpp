// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "StructureAttributeSet.h"
#include "Gameplay/Attributes/AttributeMacros.h"
#include "Gameplay/Attributes/DetectabilityAttributeSet.h"
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Gameplay/Attributes/ResistanceAttributeSet.h"
#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "UObject/Object.h"
#include "StructureGameplay.generated.h"

class UStructureAbility;
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
	TObjectPtr<UDetectabilityAttributeSet> DetectabilityAttributes;

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

	ATTRIBUTE_PASSTHROUGH(IntegrityAttributes, MaxIntegrity);
	ATTRIBUTE_PASSTHROUGH(IntegrityAttributes, Integrity);
	ATTRIBUTE_PASSTHROUGH_WithPrefix(IntegrityAttributes, Regeneration, Integrity);

	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, KineticResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ExplosiveResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ThermalResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ElectromagneticResistance);

	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, MaxIntegrityBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, MaxIntegrityMultiplier);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, RegenerationBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, RegenerationMultiplier);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, KineticResistanceBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, KineticResistanceMultiplier);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ExplosiveResistanceBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ExplosiveResistanceMultiplier);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ThermalResistanceBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ThermalResistanceMultiplier);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ElectromagneticResistanceBonus);
	ATTRIBUTE_PASSTHROUGH(ShieldAttributes, ElectromagneticResistanceMultiplier);

	ATTRIBUTE_PASSTHROUGH(EnergyAttributes, MaxEnergy);
	ATTRIBUTE_PASSTHROUGH(EnergyAttributes, Energy);
	ATTRIBUTE_PASSTHROUGH_WithPrefix(EnergyAttributes, Regeneration, Energy);

	ATTRIBUTE_PASSTHROUGH(LayoutAttributes, MaxUpkeep);
	ATTRIBUTE_PASSTHROUGH(LayoutAttributes, Upkeep);

	ATTRIBUTE_PASSTHROUGH(DetectabilityAttributes, RadarCrossSection);

	ATTRIBUTE_PASSTHROUGH(AttributeSet, LinearAcceleration);
	ATTRIBUTE_PASSTHROUGH(AttributeSet, LinearMaxSpeed);
	ATTRIBUTE_PASSTHROUGH(AttributeSet, AngularAcceleration);
	ATTRIBUTE_PASSTHROUGH(AttributeSet, AngularMaxSpeed);
	ATTRIBUTE_PASSTHROUGH(AttributeSet, SensorStrength);

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
