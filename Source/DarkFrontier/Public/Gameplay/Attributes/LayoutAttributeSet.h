// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LayoutAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API ULayoutAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxUpkeep)
	FGameplayAttributeData MaxUpkeep;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Upkeep)
	FGameplayAttributeData Upkeep;

public:

	ATTRIBUTE_ACCESSORS(ULayoutAttributeSet, MaxUpkeep);
	ATTRIBUTE_ACCESSORS(ULayoutAttributeSet, Upkeep);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxUpkeep(const FGameplayAttributeData& OldMaxUpkeep);

	UFUNCTION()
	virtual void OnRep_Upkeep(const FGameplayAttributeData& OldUpkeep);
	
};
