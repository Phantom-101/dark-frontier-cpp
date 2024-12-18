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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxIntegrity)
	FGameplayAttributeData MaxIntegrity;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Integrity)
	FGameplayAttributeData Integrity;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Regeneration)
	FGameplayAttributeData Regeneration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_KineticResistance)
	FGameplayAttributeData KineticResistance;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ExplosiveResistance)
	FGameplayAttributeData ExplosiveResistance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ThermalResistance)
	FGameplayAttributeData ThermalResistance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ElectromagneticResistance)
	FGameplayAttributeData ElectromagneticResistance;

public:

	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, MaxIntegrity);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, Integrity);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, Regeneration);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, KineticResistance);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ExplosiveResistance);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ThermalResistance);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, ElectromagneticResistance);

protected:

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxIntegrity(const FGameplayAttributeData& OldMaxIntegrity);

	UFUNCTION()
	virtual void OnRep_Integrity(const FGameplayAttributeData& OldIntegrity);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);

	UFUNCTION()
	virtual void OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance);

	UFUNCTION()
	virtual void OnRep_ExplosiveResistance(const FGameplayAttributeData& OldExplosiveResistance);

	UFUNCTION()
	virtual void OnRep_ThermalResistance(const FGameplayAttributeData& OldThermalResistance);

	UFUNCTION()
	virtual void OnRep_ElectromagneticResistance(const FGameplayAttributeData& OldElectromagneticResistance);
	
};
