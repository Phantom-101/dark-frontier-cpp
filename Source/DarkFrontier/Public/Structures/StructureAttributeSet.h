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
	
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearAcceleration);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, LinearMaxSpeed);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularAcceleration);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, AngularMaxSpeed);
	ATTRIBUTE_ACCESSORS(UStructureAttributeSet, SensorStrength);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

};
