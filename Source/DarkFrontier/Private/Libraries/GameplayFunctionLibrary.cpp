// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/GameplayFunctionLibrary.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"

TArray<FGameplayModifierInfo> UGameplayFunctionLibrary::OfAttribute(
	UGameplayEffect* Effect, const FGameplayAttribute Attribute)
{
	TArray<FGameplayModifierInfo> Modifiers;
	for(const FGameplayModifierInfo& Modifier : Effect->Modifiers)
	{
		if(Modifier.Attribute == Attribute)
		{
			Modifiers.Add(Modifier);
		}
	}
	return Modifiers;
}

TArray<FGameplayModifierInfo> UGameplayFunctionLibrary::OfAttributeAndType(
	UGameplayEffect* Effect, const FGameplayAttribute Attribute, const EGameplayModOp::Type Type)
{
	TArray<FGameplayModifierInfo> Modifiers;
	for(const FGameplayModifierInfo& Modifier : Effect->Modifiers)
	{
		if(Modifier.Attribute == Attribute && Modifier.ModifierOp == Type)
		{
			Modifiers.Add(Modifier);
		}
	}
	return Modifiers;
}

float UGameplayFunctionLibrary::Aggregate(UGameplayEffect* Effect, const FGameplayAttribute Attribute,
                                                   const EGameplayModOp::Type Type)
{
	const float Bias = GameplayEffectUtilities::GetModifierBiasByModifierOp(Type);
	float Result = Bias;
	for(const FGameplayModifierInfo& Modifier : OfAttributeAndType(Effect, Attribute, Type))
	{
		Result += GetMagnitude(Modifier) - Bias;
	}
	return Result;
}

float UGameplayFunctionLibrary::GetMagnitude(const FGameplayModifierInfo Modifier)
{
	float Magnitude = GameplayEffectUtilities::GetModifierBiasByModifierOp(Modifier.ModifierOp);
	Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Magnitude);
	return Magnitude;
}
