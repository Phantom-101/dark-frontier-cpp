// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UStructureAttributeSet::UStructureAttributeSet()
{
}

void UStructureAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHullAttribute())
	{
		SetHull(FMath::Clamp(GetHull(), 0, GetMaxHull()));
	}
	else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(FMath::Clamp(GetShield(), 0, GetMaxShield()));
	}
	else if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), 0, GetMaxEnergy()));
	}
}

void UStructureAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxHull, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Hull, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullKineticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullExplosiveResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullThermalResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullElectromagneticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxShield, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldRegen, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldKineticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldExplosiveResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldThermalResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldElectromagneticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxEnergy, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, EnergyRegen, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxUpkeep, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Upkeep, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, UpkeepReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, LinearAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, LinearMaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, AngularAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, AngularMaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, SensorStrength, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, SignatureVisibility, COND_None, REPNOTIFY_OnChanged);
}

void UStructureAttributeSet::OnRep_MaxHull(const FGameplayAttributeData& OldMaxHull)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, MaxHull, OldMaxHull);
}

void UStructureAttributeSet::OnRep_Hull(const FGameplayAttributeData& OldHull)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, Hull, OldHull);
}

void UStructureAttributeSet::OnRep_HullKineticResistance(const FGameplayAttributeData& OldHullKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullKineticResistance, OldHullKineticResistance);
}

void UStructureAttributeSet::OnRep_HullExplosiveResistance(const FGameplayAttributeData& OldHullExplosiveResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullExplosiveResistance, OldHullExplosiveResistance);
}

void UStructureAttributeSet::OnRep_HullThermalResistance(const FGameplayAttributeData& OldHullThermalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullThermalResistance, OldHullThermalResistance);
}

void UStructureAttributeSet::OnRep_HullElectromagneticResistance(const FGameplayAttributeData& OldHullElectromagneticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullElectromagneticResistance, OldHullElectromagneticResistance);
}

void UStructureAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, MaxShield, OldMaxShield);
}

void UStructureAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, Shield, OldShield);
}

void UStructureAttributeSet::OnRep_ShieldRegen(const FGameplayAttributeData& OldShieldRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldRegen, OldShieldRegen);
}

void UStructureAttributeSet::OnRep_ShieldKineticResistance(const FGameplayAttributeData& OldShieldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldKineticResistance, OldShieldKineticResistance);
}

void UStructureAttributeSet::OnRep_ShieldExplosiveResistance(const FGameplayAttributeData& OldShieldExplosiveResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldExplosiveResistance, OldShieldExplosiveResistance);
}

void UStructureAttributeSet::OnRep_ShieldThermalResistance(const FGameplayAttributeData& OldShieldThermalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldThermalResistance, OldShieldThermalResistance);
}

void UStructureAttributeSet::OnRep_ShieldElectromagneticResistance(const FGameplayAttributeData& OldShieldElectromagneticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldElectromagneticResistance, OldShieldElectromagneticResistance);
}

void UStructureAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UStructureAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, Energy, OldEnergy);
}

void UStructureAttributeSet::OnRep_EnergyRegen(const FGameplayAttributeData& OldEnergyRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, EnergyRegen, OldEnergyRegen);
}

void UStructureAttributeSet::OnRep_MaxUpkeep(const FGameplayAttributeData& OldMaxUpkeep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, MaxUpkeep, OldMaxUpkeep);
}

void UStructureAttributeSet::OnRep_Upkeep(const FGameplayAttributeData& OldUpkeep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, Upkeep, OldUpkeep);
}

void UStructureAttributeSet::OnRep_UpkeepReduction(const FGameplayAttributeData& OldUpkeepReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, UpkeepReduction, OldUpkeepReduction);
}

void UStructureAttributeSet::OnRep_LinearAcceleration(const FGameplayAttributeData& OldLinearAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, LinearAcceleration, OldLinearAcceleration);
}

void UStructureAttributeSet::OnRep_LinearMaxSpeed(const FGameplayAttributeData& OldLinearMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, LinearMaxSpeed, OldLinearMaxSpeed);
}

void UStructureAttributeSet::OnRep_AngularAcceleration(const FGameplayAttributeData& OldAngularAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, AngularAcceleration, OldAngularAcceleration);
}

void UStructureAttributeSet::OnRep_AngularMaxSpeed(const FGameplayAttributeData& OldAngularMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, AngularMaxSpeed, OldAngularMaxSpeed);
}

void UStructureAttributeSet::OnRep_SensorStrength(const FGameplayAttributeData& OldSensorStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, SensorStrength, OldSensorStrength);
}

void UStructureAttributeSet::OnRep_SignatureVisibility(const FGameplayAttributeData& OldSignatureVisibility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, SignatureVisibility, OldSignatureVisibility);
}
