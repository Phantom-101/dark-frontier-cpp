// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "HullAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHullAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHull)
	FGameplayAttributeData MaxHull;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Hull)
	FGameplayAttributeData Hull;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Regeneration)
	FGameplayAttributeData Regeneration;

public:

	ATTRIBUTE_ACCESSORS(UHullAttributeSet, MaxHull);
	ATTRIBUTE_ACCESSORS(UHullAttributeSet, Hull);
	ATTRIBUTE_ACCESSORS(UHullAttributeSet, Regeneration);

protected:

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxHull(const FGameplayAttributeData& OldMaxHull);

	UFUNCTION()
	virtual void OnRep_Hull(const FGameplayAttributeData& OldHull);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);
	
};
