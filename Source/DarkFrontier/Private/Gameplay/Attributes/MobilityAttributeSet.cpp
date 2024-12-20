// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/MobilityAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UMobilityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMobilityAttributeSet, LinearAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobilityAttributeSet, LinearMaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobilityAttributeSet, AngularAcceleration, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobilityAttributeSet, AngularMaxSpeed, COND_None, REPNOTIFY_OnChanged);
}

void UMobilityAttributeSet::OnRep_LinearAcceleration(const FGameplayAttributeData& OldLinearAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobilityAttributeSet, LinearAcceleration, OldLinearAcceleration);
}

void UMobilityAttributeSet::OnRep_LinearMaxSpeed(const FGameplayAttributeData& OldLinearMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobilityAttributeSet, LinearMaxSpeed, OldLinearMaxSpeed);
}

void UMobilityAttributeSet::OnRep_AngularAcceleration(const FGameplayAttributeData& OldAngularAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobilityAttributeSet, AngularAcceleration, OldAngularAcceleration);
}

void UMobilityAttributeSet::OnRep_AngularMaxSpeed(const FGameplayAttributeData& OldAngularMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobilityAttributeSet, AngularMaxSpeed, OldAngularMaxSpeed);
}
