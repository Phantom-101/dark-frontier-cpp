// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UEnergyAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxEnergy());
	}
}

void UEnergyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEnergyAttributeSet, MaxEnergy, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnergyAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnergyAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
}

void UEnergyAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnergyAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UEnergyAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnergyAttributeSet, Energy, OldEnergy);
}

void UEnergyAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnergyAttributeSet, Regeneration, OldRegeneration);
}
