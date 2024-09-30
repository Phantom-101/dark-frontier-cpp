// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/DetectabilityAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UDetectabilityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDetectabilityAttributeSet, RadarCrossSection, COND_None, REPNOTIFY_OnChanged);
}

void UDetectabilityAttributeSet::OnRep_RadarCrossSection(const FGameplayAttributeData& OldRadarCrossSection)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDetectabilityAttributeSet, RadarCrossSection, OldRadarCrossSection);
}
