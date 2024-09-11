// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ResistanceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UResistanceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_KineticResistance)
	FGameplayAttributeData KineticResistance;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ExplosiveResistance)
	FGameplayAttributeData ExplosiveResistance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ThermalResistance)
	FGameplayAttributeData ThermalResistance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ElectromagneticResistance)
	FGameplayAttributeData ElectromagneticResistance;

public:

	ATTRIBUTE_ACCESSORS(UResistanceAttributeSet, KineticResistance);
	ATTRIBUTE_ACCESSORS(UResistanceAttributeSet, ExplosiveResistance);
	ATTRIBUTE_ACCESSORS(UResistanceAttributeSet, ThermalResistance);
	ATTRIBUTE_ACCESSORS(UResistanceAttributeSet, ElectromagneticResistance);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance);

	UFUNCTION()
	virtual void OnRep_ExplosiveResistance(const FGameplayAttributeData& OldExplosiveResistance);

	UFUNCTION()
	virtual void OnRep_ThermalResistance(const FGameplayAttributeData& OldThermalResistance);

	UFUNCTION()
	virtual void OnRep_ElectromagneticResistance(const FGameplayAttributeData& OldElectromagneticResistance);
	
};
