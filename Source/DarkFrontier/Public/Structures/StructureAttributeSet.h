// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "StructureAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxHull)
	FGameplayAttributeData MaxHull;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Hull)
	FGameplayAttributeData Hull;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullKineticResistance)
	FGameplayAttributeData HullKineticResistance;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullExplosiveResistance)
	FGameplayAttributeData HullExplosiveResistance;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullThermalResistance)
	FGameplayAttributeData HullThermalResistance;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullElectromagneticResistance)
	FGameplayAttributeData HullElectromagneticResistance;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldRegen)
	FGameplayAttributeData ShieldRegen;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldKineticResistance)
	FGameplayAttributeData ShieldKineticResistance;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldExplosiveResistance)
	FGameplayAttributeData ShieldExplosiveResistance;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldThermalResistance)
	FGameplayAttributeData ShieldThermalResistance;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldElectromagneticResistance)
	FGameplayAttributeData ShieldElectromagneticResistance;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_EnergyRegen)
	FGameplayAttributeData EnergyRegen;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxUpkeep)
	FGameplayAttributeData MaxUpkeep;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Upkeep)
	FGameplayAttributeData Upkeep;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_UpkeepReduction)
	FGameplayAttributeData UpkeepReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_LinearAcceleration)
	FGameplayAttributeData LinearAcceleration;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_LinearMaxSpeed)
	FGameplayAttributeData LinearMaxSpeed;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_AngularAcceleration)
	FGameplayAttributeData AngularAcceleration;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_AngularMaxSpeed)
	FGameplayAttributeData AngularMaxSpeed;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_SensorStrength)
	FGameplayAttributeData SensorStrength;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_SignatureVisibility)
	FGameplayAttributeData SignatureVisibility;

	UStructureAttributeSet();

	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxHull);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Hull);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullKineticResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullExplosiveResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullThermalResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullElectromagneticResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldRegen);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldKineticResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldExplosiveResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldThermalResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldElectromagneticResistance);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxEnergy);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Energy);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, EnergyRegen);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxUpkeep);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Upkeep);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, UpkeepReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearAcceleration);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearMaxSpeed);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularAcceleration);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularMaxSpeed);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, SensorStrength);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, SignatureVisibility);
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxHull(const FGameplayAttributeData& OldMaxHull);

	UFUNCTION()
	virtual void OnRep_Hull(const FGameplayAttributeData& OldHull);

	UFUNCTION()
	virtual void OnRep_HullKineticResistance(const FGameplayAttributeData& OldHullKineticResistance);

	UFUNCTION()
	virtual void OnRep_HullExplosiveResistance(const FGameplayAttributeData& OldHullExplosiveResistance);

	UFUNCTION()
	virtual void OnRep_HullThermalResistance(const FGameplayAttributeData& OldHullThermalResistance);

	UFUNCTION()
	virtual void OnRep_HullElectromagneticResistance(const FGameplayAttributeData& OldHullElectromagneticResistance);

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UFUNCTION()
	virtual void OnRep_ShieldRegen(const FGameplayAttributeData& OldShieldRegen);

	UFUNCTION()
	virtual void OnRep_ShieldKineticResistance(const FGameplayAttributeData& OldShieldKineticResistance);

	UFUNCTION()
	virtual void OnRep_ShieldExplosiveResistance(const FGameplayAttributeData& OldShieldExplosiveResistance);

	UFUNCTION()
	virtual void OnRep_ShieldThermalResistance(const FGameplayAttributeData& OldShieldThermalResistance);

	UFUNCTION()
	virtual void OnRep_ShieldElectromagneticResistance(const FGameplayAttributeData& OldShieldElectromagneticResistance);
	
	UFUNCTION()
	virtual void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);
	
	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);
	
	UFUNCTION()
	virtual void OnRep_EnergyRegen(const FGameplayAttributeData& OldEnergyRegen);
	
	UFUNCTION()
	virtual void OnRep_MaxUpkeep(const FGameplayAttributeData& OldMaxUpkeep);
	
	UFUNCTION()
	virtual void OnRep_Upkeep(const FGameplayAttributeData& OldUpkeep);
	
	UFUNCTION()
	virtual void OnRep_UpkeepReduction(const FGameplayAttributeData& OldUpkeepReduction);
	
	UFUNCTION()
	virtual void OnRep_LinearAcceleration(const FGameplayAttributeData& OldLinearAcceleration);
	
	UFUNCTION()
	virtual void OnRep_LinearMaxSpeed(const FGameplayAttributeData& OldLinearMaxSpeed);
	
	UFUNCTION()
	virtual void OnRep_AngularAcceleration(const FGameplayAttributeData& OldAngularAcceleration);
	
	UFUNCTION()
	virtual void OnRep_AngularMaxSpeed(const FGameplayAttributeData& OldAngularMaxSpeed);

	UFUNCTION()
	virtual void OnRep_SensorStrength(const FGameplayAttributeData& OldSensorStrength);

	UFUNCTION()
	virtual void OnRep_SignatureVisibility(const FGameplayAttributeData& OldSignatureVisibility);
};
