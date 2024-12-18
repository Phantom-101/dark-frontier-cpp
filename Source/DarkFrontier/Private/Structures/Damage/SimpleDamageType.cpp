// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Damage/SimpleDamageType.h"
#include "AbilitySystemComponent.h"

float USimpleDamageType::Evaluate(const UTargetGroup* TargetGroup, const UAbilitySystemComponent* Comp) const
{
	if(ResistanceAttributes.Contains(TargetGroup))
	{
		const FGameplayAttribute Attribute = ResistanceAttributes[TargetGroup];
		return FMath::Exp(-Comp->GetNumericAttribute(Attribute));
	}

	return 1;
}
