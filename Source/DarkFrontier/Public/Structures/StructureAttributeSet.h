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

	UStructureAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxHull)
	FGameplayAttributeData MaxHull;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxHull);

	UFUNCTION()
	virtual void OnRep_MaxHull(const FGameplayAttributeData& OldMaxHull);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Hull)
	FGameplayAttributeData Hull;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Hull);

	UFUNCTION()
	virtual void OnRep_Hull(const FGameplayAttributeData& OldHull);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullKineticDamageReduction)
	FGameplayAttributeData HullKineticDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullKineticDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullKineticDamageReduction(const FGameplayAttributeData& OldHullKineticDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullExplosiveDamageReduction)
	FGameplayAttributeData HullExplosiveDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullExplosiveDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullExplosiveDamageReduction(const FGameplayAttributeData& OldHullExplosiveDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullBeamDamageReduction)
	FGameplayAttributeData HullBeamDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullBeamDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullBeamDamageReduction(const FGameplayAttributeData& OldHullBeamDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullFieldDamageReduction)
	FGameplayAttributeData HullFieldDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullFieldDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullFieldDamageReduction(const FGameplayAttributeData& OldHullFieldDamageReduction);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxShield);

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Shield);

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldRegen)
	FGameplayAttributeData ShieldRegen;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldRegen);

	UFUNCTION()
	virtual void OnRep_ShieldRegen(const FGameplayAttributeData& OldShieldRegen);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldKineticDamageReduction)
	FGameplayAttributeData ShieldKineticDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldKineticDamageReduction);

	UFUNCTION()
	virtual void OnRep_ShieldKineticDamageReduction(const FGameplayAttributeData& OldShieldKineticDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldExplosiveDamageReduction)
	FGameplayAttributeData ShieldExplosiveDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldExplosiveDamageReduction);

	UFUNCTION()
	virtual void OnRep_ShieldExplosiveDamageReduction(const FGameplayAttributeData& OldShieldExplosiveDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldBeamDamageReduction)
	FGameplayAttributeData ShieldBeamDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldBeamDamageReduction);

	UFUNCTION()
	virtual void OnRep_ShieldBeamDamageReduction(const FGameplayAttributeData& OldShieldBeamDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldFieldDamageReduction)
	FGameplayAttributeData ShieldFieldDamageReduction;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldFieldDamageReduction);

	UFUNCTION()
	virtual void OnRep_ShieldFieldDamageReduction(const FGameplayAttributeData& OldShieldFieldDamageReduction);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxEnergy);

	UFUNCTION()
	virtual void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Energy);

	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_EnergyRegen)
	FGameplayAttributeData EnergyRegen;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, EnergyRegen);

	UFUNCTION()
	virtual void OnRep_EnergyRegen(const FGameplayAttributeData& OldEnergyRegen);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_LinearAcceleration)
	FGameplayAttributeData LinearAcceleration;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearAcceleration);

	UFUNCTION()
	virtual void OnRep_LinearAcceleration(const FGameplayAttributeData& OldLinearAcceleration);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_LinearMaxSpeed)
	FGameplayAttributeData LinearMaxSpeed;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearMaxSpeed);

	UFUNCTION()
	virtual void OnRep_LinearMaxSpeed(const FGameplayAttributeData& OldLinearMaxSpeed);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_AngularAcceleration)
	FGameplayAttributeData AngularAcceleration;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularAcceleration);

	UFUNCTION()
	virtual void OnRep_AngularAcceleration(const FGameplayAttributeData& OldAngularAcceleration);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_AngularMaxSpeed)
	FGameplayAttributeData AngularMaxSpeed;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularMaxSpeed);

	UFUNCTION()
	virtual void OnRep_AngularMaxSpeed(const FGameplayAttributeData& OldAngularMaxSpeed);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_SensorStrength)
	FGameplayAttributeData SensorStrength;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, SensorStrength);

	UFUNCTION()
	virtual void OnRep_SensorStrength(const FGameplayAttributeData& OldSensorStrength);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_SignatureVisibility)
	FGameplayAttributeData SignatureVisibility;
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, SignatureVisibility);

	UFUNCTION()
	virtual void OnRep_SignatureVisibility(const FGameplayAttributeData& OldSignatureVisibility);
};
