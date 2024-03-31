// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplayAbility.h"
#include "AbilitySystemComponent.h"

UStructureGameplayAbility::UStructureGameplayAbility()
{
}

bool UStructureGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if(!GetCostGameplayEffect()) return true;
	
	FGameplayEffectSpec	Spec(GetCostGameplayEffect(), MakeEffectContext(Handle, ActorInfo), GetAbilityLevel(Handle, ActorInfo));
	for(const TPair<FGameplayTag, float> Pair : CostSetByCallerMagnitudes)
	{
		Spec.SetSetByCallerMagnitude(Pair.Key, Pair.Value);
	}

	Spec.CalculateModifierMagnitudes();
	
	for(int32 ModIdx = 0; ModIdx < Spec.Modifiers.Num(); ++ModIdx)
	{
		const FGameplayModifierInfo& ModDef = Spec.Def->Modifiers[ModIdx];
		const FModifierSpec& ModSpec = Spec.Modifiers[ModIdx];
	
		// It only makes sense to check additive operators
		if (ModDef.ModifierOp == EGameplayModOp::Additive)
		{
			if (!ModDef.Attribute.IsValid())
			{
				continue;
			}
			const UAttributeSet* Set = ActorInfo->AbilitySystemComponent.Get()->GetAttributeSet(ModDef.Attribute.GetAttributeSetClass());
			const float CurrentValue = ModDef.Attribute.GetNumericValueChecked(Set);
			const float CostValue = ModSpec.GetEvaluatedMagnitude();

			if (CurrentValue + CostValue < 0.f)
			{
				return false;
			}
		}
	}
	return true;
}

void UStructureGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if(!GetCostGameplayEffect()) return;
	if(!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, CostGameplayEffectClass, GetAbilityLevel(Handle, ActorInfo));
	if (SpecHandle.IsValid())
	{
		for(const TPair<FGameplayTag, float> Pair : CostSetByCallerMagnitudes)
		{
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(Pair.Key, Pair.Value);
		}
		(void)ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
