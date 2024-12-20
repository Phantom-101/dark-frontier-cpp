// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/DetectionAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UDetectionAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDetectionAttributeSet, Detection, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDetectionAttributeSet, Detectability, COND_None, REPNOTIFY_OnChanged);
}

void UDetectionAttributeSet::OnRep_Detection(const FGameplayAttributeData& OldDetection)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDetectionAttributeSet, Detection, OldDetection);
}

void UDetectionAttributeSet::OnRep_Detectability(const FGameplayAttributeData& OldDetectability)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDetectionAttributeSet, Detectability, OldDetectability);
}
