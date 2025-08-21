// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayFunctionLibrary.generated.h"

class UGameplayEffect;
struct FGameplayAttribute;
struct FGameplayModifierInfo;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static TArray<FGameplayModifierInfo> OfAttribute(UGameplayEffect* Effect, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintPure)
	static TArray<FGameplayModifierInfo> OfAttributeAndType(UGameplayEffect* Effect, FGameplayAttribute Attribute,
	                                                        EGameplayModOp::Type Type);

	UFUNCTION(BlueprintPure)
	static float Aggregate(UGameplayEffect* Effect, FGameplayAttribute Attribute, EGameplayModOp::Type Type);

	UFUNCTION(BlueprintPure)
	static float GetMagnitude(FGameplayModifierInfo Modifier);
};
