// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UShieldAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxShield());
	}
}

void UShieldAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, MaxShield, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
}

void UShieldAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, MaxShield, OldMaxShield);
}

void UShieldAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, Shield, OldShield);
}

void UShieldAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, Regeneration, OldRegeneration);
}
