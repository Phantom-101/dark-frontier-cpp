// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/ResistanceAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UResistanceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UResistanceAttributeSet, KineticResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UResistanceAttributeSet, ExplosiveResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UResistanceAttributeSet, ThermalResistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UResistanceAttributeSet, ElectromagneticResistance, COND_None, REPNOTIFY_OnChanged);
}

void UResistanceAttributeSet::OnRep_KineticResistance(const FGameplayAttributeData& OldKineticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResistanceAttributeSet, KineticResistance, OldKineticResistance);
}

void UResistanceAttributeSet::OnRep_ExplosiveResistance(const FGameplayAttributeData& OldExplosiveResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResistanceAttributeSet, ExplosiveResistance, OldExplosiveResistance);
}

void UResistanceAttributeSet::OnRep_ThermalResistance(const FGameplayAttributeData& OldThermalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResistanceAttributeSet, ThermalResistance, OldThermalResistance);
}

void UResistanceAttributeSet::OnRep_ElectromagneticResistance(const FGameplayAttributeData& OldElectromagneticResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UResistanceAttributeSet, ElectromagneticResistance, OldElectromagneticResistance);
}
