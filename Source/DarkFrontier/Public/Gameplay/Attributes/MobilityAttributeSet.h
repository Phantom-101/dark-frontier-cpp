// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MobilityAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UMobilityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_LinearAcceleration)
	FGameplayAttributeData LinearAcceleration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_LinearMaxSpeed)
	FGameplayAttributeData LinearMaxSpeed;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AngularAcceleration)
	FGameplayAttributeData AngularAcceleration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AngularMaxSpeed)
	FGameplayAttributeData AngularMaxSpeed;

public:

	ATTRIBUTE_ACCESSORS(UMobilityAttributeSet, LinearAcceleration);
	ATTRIBUTE_ACCESSORS(UMobilityAttributeSet, LinearMaxSpeed);
	ATTRIBUTE_ACCESSORS(UMobilityAttributeSet, AngularAcceleration);
	ATTRIBUTE_ACCESSORS(UMobilityAttributeSet, AngularMaxSpeed);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_LinearAcceleration(const FGameplayAttributeData& OldLinearAcceleration);
	
	UFUNCTION()
	virtual void OnRep_LinearMaxSpeed(const FGameplayAttributeData& OldLinearMaxSpeed);
	
	UFUNCTION()
	virtual void OnRep_AngularAcceleration(const FGameplayAttributeData& OldAngularAcceleration);
	
	UFUNCTION()
	virtual void OnRep_AngularMaxSpeed(const FGameplayAttributeData& OldAngularMaxSpeed);
	
};
