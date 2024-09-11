// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "IntegrityAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UIntegrityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxIntegrity)
	FGameplayAttributeData MaxIntegrity;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Integrity)
	FGameplayAttributeData Integrity;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Regeneration)
	FGameplayAttributeData Regeneration;

public:

	ATTRIBUTE_ACCESSORS(UIntegrityAttributeSet, MaxIntegrity);
	ATTRIBUTE_ACCESSORS(UIntegrityAttributeSet, Integrity);
	ATTRIBUTE_ACCESSORS(UIntegrityAttributeSet, Regeneration);

protected:

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxIntegrity(const FGameplayAttributeData& OldMaxIntegrity);

	UFUNCTION()
	virtual void OnRep_Integrity(const FGameplayAttributeData& OldIntegrity);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);
	
};
