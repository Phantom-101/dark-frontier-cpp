// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DetectionAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UDetectionAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Detection)
	FGameplayAttributeData Detection;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Detectability)
	FGameplayAttributeData Detectability;

public:

	ATTRIBUTE_ACCESSORS(UDetectionAttributeSet, Detection);
	ATTRIBUTE_ACCESSORS(UDetectionAttributeSet, Detectability);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Detection(const FGameplayAttributeData& OldDetection);

	UFUNCTION()
	virtual void OnRep_Detectability(const FGameplayAttributeData& OldDetectability);
	
};
