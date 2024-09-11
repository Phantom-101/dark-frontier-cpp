// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UShieldAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, MaxIntegrityBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, MaxIntegrityMultiplier, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, RegenerationBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, RegenerationMultiplier, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, KineticResistanceBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, KineticResistanceMultiplier, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ExplosiveResistanceBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ExplosiveResistanceMultiplier, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ThermalResistanceBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ThermalResistanceMultiplier, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ElectromagneticResistanceBonus, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ElectromagneticResistanceMultiplier, COND_None, REPNOTIFY_OnChanged);
}

void UShieldAttributeSet::OnRep_MaxIntegrityBonus(const FGameplayAttributeData& OldMaxIntegrityBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, MaxIntegrityBonus, OldMaxIntegrityBonus);
}

void UShieldAttributeSet::OnRep_MaxIntegrityMultiplier(const FGameplayAttributeData& OldMaxIntegrityMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, MaxIntegrityMultiplier, OldMaxIntegrityMultiplier);
}

void UShieldAttributeSet::OnRep_RegenerationBonus(const FGameplayAttributeData& OldRegenerationBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, RegenerationBonus, OldRegenerationBonus);
}

void UShieldAttributeSet::OnRep_RegenerationMultiplier(const FGameplayAttributeData& OldRegenerationMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, RegenerationMultiplier, OldRegenerationMultiplier);
}

void UShieldAttributeSet::OnRep_KineticResistanceBonus(const FGameplayAttributeData& OldKineticResistanceBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, KineticResistanceBonus, OldKineticResistanceBonus);
}

void UShieldAttributeSet::OnRep_KineticResistanceMultiplier(const FGameplayAttributeData& OldKineticResistanceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, KineticResistanceMultiplier, OldKineticResistanceMultiplier);
}

void UShieldAttributeSet::OnRep_ExplosiveResistanceBonus(const FGameplayAttributeData& OldExplosiveResistanceBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ExplosiveResistanceBonus, OldExplosiveResistanceBonus);
}

void UShieldAttributeSet::OnRep_ExplosiveResistanceMultiplier(const FGameplayAttributeData& OldExplosiveResistanceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ExplosiveResistanceMultiplier, OldExplosiveResistanceMultiplier);
}

void UShieldAttributeSet::OnRep_ThermalResistanceBonus(const FGameplayAttributeData& OldThermalResistanceBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ThermalResistanceBonus, OldThermalResistanceBonus);
}

void UShieldAttributeSet::OnRep_ThermalResistanceMultiplier(const FGameplayAttributeData& OldThermalResistanceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ThermalResistanceMultiplier, OldThermalResistanceMultiplier);
}

void UShieldAttributeSet::OnRep_ElectromagneticResistanceBonus(const FGameplayAttributeData& OldElectromagneticResistanceBonus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ElectromagneticResistanceBonus, OldElectromagneticResistanceBonus);
}

void UShieldAttributeSet::OnRep_ElectromagneticResistanceMultiplier(const FGameplayAttributeData& OldElectromagneticResistanceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ElectromagneticResistanceMultiplier, OldElectromagneticResistanceMultiplier);
}
