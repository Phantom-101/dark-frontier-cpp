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
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullKineticDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullExplosiveDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullBeamDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, HullFieldDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxShield, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldRegen, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldKineticDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldExplosiveDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldBeamDamageReduction, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, ShieldFieldDamageReduction, COND_None, REPNOTIFY_OnChanged);
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

void UStructureAttributeSet::OnRep_HullKineticDamageReduction(const FGameplayAttributeData& OldHullKineticDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullKineticDamageReduction, OldHullKineticDamageReduction);
}

void UStructureAttributeSet::OnRep_HullExplosiveDamageReduction(const FGameplayAttributeData& OldHullExplosiveDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullExplosiveDamageReduction, OldHullExplosiveDamageReduction);
}

void UStructureAttributeSet::OnRep_HullBeamDamageReduction(const FGameplayAttributeData& OldHullBeamDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullBeamDamageReduction, OldHullBeamDamageReduction);
}

void UStructureAttributeSet::OnRep_HullFieldDamageReduction(const FGameplayAttributeData& OldHullFieldDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, HullFieldDamageReduction, OldHullFieldDamageReduction);
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

void UStructureAttributeSet::OnRep_ShieldKineticDamageReduction(const FGameplayAttributeData& OldShieldKineticDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldKineticDamageReduction, OldShieldKineticDamageReduction);
}

void UStructureAttributeSet::OnRep_ShieldExplosiveDamageReduction(const FGameplayAttributeData& OldShieldExplosiveDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldExplosiveDamageReduction, OldShieldExplosiveDamageReduction);
}

void UStructureAttributeSet::OnRep_ShieldBeamDamageReduction(const FGameplayAttributeData& OldShieldBeamDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldBeamDamageReduction, OldShieldBeamDamageReduction);
}

void UStructureAttributeSet::OnRep_ShieldFieldDamageReduction(const FGameplayAttributeData& OldShieldFieldDamageReduction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, ShieldFieldDamageReduction, OldShieldFieldDamageReduction);
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
