// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "SignatureAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API USignatureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_RadarSignature)
	FGameplayAttributeData RadarSignature;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_InfraredSignature)
	FGameplayAttributeData InfraredSignature;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_LidarSignature)
	FGameplayAttributeData LidarSignature;

public:

	ATTRIBUTE_ACCESSORS(USignatureAttributeSet, RadarSignature);
	ATTRIBUTE_ACCESSORS(USignatureAttributeSet, InfraredSignature);
	ATTRIBUTE_ACCESSORS(USignatureAttributeSet, LidarSignature);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_RadarSignature(const FGameplayAttributeData& OldRadarSignature);

	UFUNCTION()
	virtual void OnRep_InfraredSignature(const FGameplayAttributeData& OldInfraredSignature);

	UFUNCTION()
	virtual void OnRep_LidarSignature(const FGameplayAttributeData& OldLidarSignature);
	
};
