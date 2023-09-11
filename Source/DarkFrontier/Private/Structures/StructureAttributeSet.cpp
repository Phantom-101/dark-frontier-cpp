// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UStructureAttributeSet::UStructureAttributeSet()
{
}

void UStructureAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, MaxHull, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, Hull, COND_None, REPNOTIFY_Always);
	// todo add other attributes later
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
	else if (Data.EvaluatedData.Attribute == GetChargeAttribute())
	{
		SetCharge(FMath::Clamp(GetCharge(), 0, GetMaxCharge()));
	}
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

void UStructureAttributeSet::OnRep_MaxCharge(const FGameplayAttributeData& OldMaxCharge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, MaxCharge, OldMaxCharge);
}

void UStructureAttributeSet::OnRep_Charge(const FGameplayAttributeData& OldCharge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStructureAttributeSet, Charge, OldCharge);
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
