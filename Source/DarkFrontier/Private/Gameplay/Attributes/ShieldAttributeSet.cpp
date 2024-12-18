// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UShieldAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetIntegrityAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxIntegrity());
	}
}

void UShieldAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, MaxIntegrity, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, Integrity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, KineticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ExplosiveResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ThermalResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UShieldAttributeSet, ElectromagneticResistance, COND_None, REPNOTIFY_OnChanged);
}

void UShieldAttributeSet::OnRep_MaxIntegrity(const FGameplayAttributeData& OldMaxIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, MaxIntegrity, OldMaxIntegrity);
}

void UShieldAttributeSet::OnRep_Integrity(const FGameplayAttributeData& OldIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, Integrity, OldIntegrity);
}

void UShieldAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, Regeneration, OldRegeneration);
}

void UShieldAttributeSet::OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, KineticResistance, OldKineticResistance);
}

void UShieldAttributeSet::OnRep_ExplosiveResistance(const FGameplayAttributeData& OldExplosiveResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ExplosiveResistance, OldExplosiveResistance);
}

void UShieldAttributeSet::OnRep_ThermalResistance(const FGameplayAttributeData& OldThermalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ThermalResistance, OldThermalResistance);
}

void UShieldAttributeSet::OnRep_ElectromagneticResistance(const FGameplayAttributeData& OldElectromagneticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UShieldAttributeSet, ElectromagneticResistance, OldElectromagneticResistance);
}
