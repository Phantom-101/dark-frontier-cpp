// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/HullAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UHullAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetIntegrityAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxIntegrity());
	}
}

void UHullAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, MaxIntegrity, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, Integrity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, KineticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, ExplosiveResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, ThermalResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UHullAttributeSet, ElectromagneticResistance, COND_None, REPNOTIFY_OnChanged);
}

void UHullAttributeSet::OnRep_MaxIntegrity(const FGameplayAttributeData& OldMaxIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, MaxIntegrity, OldMaxIntegrity);
}

void UHullAttributeSet::OnRep_Integrity(const FGameplayAttributeData& OldIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, Integrity, OldIntegrity);
}

void UHullAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, Regeneration, OldRegeneration);
}

void UHullAttributeSet::OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, KineticResistance, OldKineticResistance);
}

void UHullAttributeSet::OnRep_ExplosiveResistance(const FGameplayAttributeData& OldExplosiveResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, ExplosiveResistance, OldExplosiveResistance);
}

void UHullAttributeSet::OnRep_ThermalResistance(const FGameplayAttributeData& OldThermalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, ThermalResistance, OldThermalResistance);
}

void UHullAttributeSet::OnRep_ElectromagneticResistance(const FGameplayAttributeData& OldElectromagneticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHullAttributeSet, ElectromagneticResistance, OldElectromagneticResistance);
}
