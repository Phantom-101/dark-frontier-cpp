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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Regeneration)
	FGameplayAttributeData Regeneration;

public:

	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UShieldAttributeSet, Regeneration);

protected:

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);
	
};
