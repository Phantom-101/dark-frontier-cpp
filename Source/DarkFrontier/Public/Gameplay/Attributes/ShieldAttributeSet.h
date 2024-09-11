// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ShieldAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UShieldAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxIntegrityBonus)
	FGameplayAttributeData MaxIntegrityBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxIntegrityMultiplier)
	FGameplayAttributeData MaxIntegrityMultiplier;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_RegenerationBonus)
	FGameplayAttributeData RegenerationBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_RegenerationMultiplier)
	FGameplayAttributeData RegenerationMultiplier;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_KineticResistanceBonus)
	FGameplayAttributeData KineticResistanceBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_KineticResistanceMultiplier)
	FGameplayAttributeData KineticResistanceMultiplier;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ExplosiveResistanceBonus)
	FGameplayAttributeData ExplosiveResistanceBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ExplosiveResistanceMultiplier)
	FGameplayAttributeData ExplosiveResistanceMultiplier;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ThermalResistanceBonus)
	FGameplayAttributeData ThermalResistanceBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ThermalResistanceMultiplier)
	FGameplayAttributeData ThermalResistanceMultiplier;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ElectromagneticResistanceBonus)
	FGameplayAttributeData ElectromagneticResistanceBonus;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ElectromagneticResistanceMultiplier)
	FGameplayAttributeData ElectromagneticResistanceMultiplier;

public:

	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, MaxIntegrityBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, MaxIntegrityMultiplier);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, RegenerationBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, RegenerationMultiplier);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, KineticResistanceBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, KineticResistanceMultiplier);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ExplosiveResistanceBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ExplosiveResistanceMultiplier);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ThermalResistanceBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ThermalResistanceMultiplier);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ElectromagneticResistanceBonus);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ElectromagneticResistanceMultiplier);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxIntegrityBonus(const FGameplayAttributeData& OldMaxIntegrityBonus);

	UFUNCTION()
	virtual void OnRep_MaxIntegrityMultiplier(const FGameplayAttributeData& OldMaxIntegrityMultiplier);

	UFUNCTION()
	virtual void OnRep_RegenerationBonus(const FGameplayAttributeData& OldRegenerationBonus);

	UFUNCTION()
	virtual void OnRep_RegenerationMultiplier(const FGameplayAttributeData& OldRegenerationMultiplier);
	
	UFUNCTION()
	virtual void OnRep_KineticResistanceBonus(const FGameplayAttributeData& OldKineticResistanceBonus);
	
	UFUNCTION()
	virtual void OnRep_KineticResistanceMultiplier(const FGameplayAttributeData& OldKineticResistanceMultiplier);

	UFUNCTION()
	virtual void OnRep_ExplosiveResistanceBonus(const FGameplayAttributeData& OldExplosiveResistanceBonus);
	
	UFUNCTION()
	virtual void OnRep_ExplosiveResistanceMultiplier(const FGameplayAttributeData& OldExplosiveResistanceMultiplier);

	UFUNCTION()
	virtual void OnRep_ThermalResistanceBonus(const FGameplayAttributeData& OldThermalResistanceBonus);
	
	UFUNCTION()
	virtual void OnRep_ThermalResistanceMultiplier(const FGameplayAttributeData& OldThermalResistanceMultiplier);

	UFUNCTION()
	virtual void OnRep_ElectromagneticResistanceBonus(const FGameplayAttributeData& OldElectromagneticResistanceBonus);
	
	UFUNCTION()
	virtual void OnRep_ElectromagneticResistanceMultiplier(const FGameplayAttributeData& OldElectromagneticResistanceMultiplier);
	
};
