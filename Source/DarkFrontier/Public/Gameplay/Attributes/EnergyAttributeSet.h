// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EnergyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UEnergyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Regeneration)
	FGameplayAttributeData Regeneration;

public:

	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, MaxEnergy);
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Energy);
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Regeneration);

protected:

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);

	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);
	
};
