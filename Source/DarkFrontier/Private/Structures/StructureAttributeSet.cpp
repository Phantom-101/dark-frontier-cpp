// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UStructureAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, LinearAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, LinearMaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, AngularAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, AngularMaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UStructureAttributeSet, SensorStrength, COND_None, REPNOTIFY_OnChanged);
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
