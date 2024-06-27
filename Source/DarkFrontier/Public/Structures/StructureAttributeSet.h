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
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullKineticDamageReduction)
	FGameplayAttributeData HullKineticDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullExplosiveDamageReduction)
	FGameplayAttributeData HullExplosiveDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullBeamDamageReduction)
	FGameplayAttributeData HullBeamDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_HullFieldDamageReduction)
	FGameplayAttributeData HullFieldDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldRegen)
	FGameplayAttributeData ShieldRegen;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldKineticDamageReduction)
	FGameplayAttributeData ShieldKineticDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldExplosiveDamageReduction)
	FGameplayAttributeData ShieldExplosiveDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldBeamDamageReduction)
	FGameplayAttributeData ShieldBeamDamageReduction;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_ShieldFieldDamageReduction)
	FGameplayAttributeData ShieldFieldDamageReduction;

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
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullKineticDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullExplosiveDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullBeamDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, HullFieldDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldRegen);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldKineticDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldExplosiveDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldBeamDamageReduction);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, ShieldFieldDamageReduction);
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
	virtual void OnRep_HullKineticDamageReduction(const FGameplayAttributeData& OldHullKineticDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullExplosiveDamageReduction(const FGameplayAttributeData& OldHullExplosiveDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullBeamDamageReduction(const FGameplayAttributeData& OldHullBeamDamageReduction);

	UFUNCTION()
	virtual void OnRep_HullFieldDamageReduction(const FGameplayAttributeData& OldHullFieldDamageReduction);

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UFUNCTION()
	virtual void OnRep_ShieldRegen(const FGameplayAttributeData& OldShieldRegen);

	UFUNCTION()
	virtual void OnRep_ShieldKineticDamageReduction(const FGameplayAttributeData& OldShieldKineticDamageReduction);

	UFUNCTION()
	virtual void OnRep_ShieldExplosiveDamageReduction(const FGameplayAttributeData& OldShieldExplosiveDamageReduction);
	
	UFUNCTION()
	virtual void OnRep_ShieldBeamDamageReduction(const FGameplayAttributeData& OldShieldBeamDamageReduction);
	
	UFUNCTION()
	virtual void OnRep_ShieldFieldDamageReduction(const FGameplayAttributeData& OldShieldFieldDamageReduction);
	
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
