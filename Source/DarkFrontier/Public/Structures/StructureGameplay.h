// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Attributes/AttributeMacros.h"
#include "Gameplay/Attributes/DetectionAttributeSet.h"
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/HullAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Gameplay/Attributes/MobilityAttributeSet.h"
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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UStructureAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UHullAttributeSet> HullAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UShieldAttributeSet> ShieldAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UEnergyAttributeSet> EnergyAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<ULayoutAttributeSet> LayoutAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UDetectionAttributeSet> DetectionAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	TObjectPtr<UMobilityAttributeSet> MobilityAttributes;

public:

	static UStructureGameplay* CreateGameplay(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	void Initialize() const;

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;

	UFUNCTION(BlueprintCallable)
	FActiveGameplayEffectHandle ApplyEffect(TSubclassOf<UGameplayEffect> Effect) const;

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(FActiveGameplayEffectHandle Handle) const;

	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GiveAbility(TSubclassOf<UStructureAbility> Ability) const;

	UFUNCTION(BlueprintCallable)
	void ClearAbility(FGameplayAbilitySpecHandle Handle) const;

	virtual UStructureAbilitySystemComponent* GetAbilitySystemComponent() const;

	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, MaxIntegrity, MaxHull);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, Integrity, Hull);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, Regeneration, HullRegeneration);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, KineticResistance, HullKineticResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, ExplosiveResistance, HullExplosiveResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, ThermalResistance, HullThermalResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(HullAttributes, ElectromagneticResistance, HullElectromagneticResistance);

	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, MaxIntegrity, MaxShield);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, Integrity, Shield);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, Regeneration, ShieldRegeneration);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, KineticResistance, ShieldKineticResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, ExplosiveResistance, ShieldExplosiveResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, ThermalResistance, ShieldThermalResistance);
	ATTRIBUTE_PASSTHROUGH_ALIAS(ShieldAttributes, ElectromagneticResistance, ShieldElectromagneticResistance);

	ATTRIBUTE_PASSTHROUGH(EnergyAttributes, MaxEnergy);
	ATTRIBUTE_PASSTHROUGH(EnergyAttributes, Energy);
	ATTRIBUTE_PASSTHROUGH_ALIAS(EnergyAttributes, Regeneration, EnergyRegeneration);

	ATTRIBUTE_PASSTHROUGH(LayoutAttributes, MaxUpkeep);
	ATTRIBUTE_PASSTHROUGH(LayoutAttributes, Upkeep);

	ATTRIBUTE_PASSTHROUGH(DetectionAttributes, Detection);
	ATTRIBUTE_PASSTHROUGH(DetectionAttributes, Detectability);

	ATTRIBUTE_PASSTHROUGH(MobilityAttributes, LinearAcceleration);
	ATTRIBUTE_PASSTHROUGH(MobilityAttributes, LinearMaxSpeed);
	ATTRIBUTE_PASSTHROUGH(MobilityAttributes, AngularAcceleration);
	ATTRIBUTE_PASSTHROUGH(MobilityAttributes, AngularMaxSpeed);

	// TODO move out
	UFUNCTION(BlueprintCallable)
	bool IsDetecting(AStructure* Other) const;

	UFUNCTION(BlueprintCallable)
	void ApplyStartingEffects();

};
