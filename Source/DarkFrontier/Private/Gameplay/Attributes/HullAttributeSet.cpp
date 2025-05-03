// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/HullAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UHullAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetHullAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHull());
	}
}

void UHullAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, MaxHull, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, Hull, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
}

void UHullAttributeSet::OnRep_MaxHull(const FGameplayAttributeData& OldMaxHull)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, MaxHull, OldMaxHull);
}

void UHullAttributeSet::OnRep_Hull(const FGameplayAttributeData& OldHull)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, Hull, OldHull);
}

void UHullAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, Regeneration, OldRegeneration);
}
