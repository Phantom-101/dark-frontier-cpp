// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/SignatureAttributeSet.h"
#include "Net/UnrealNetwork.h"

void USignatureAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USignatureAttributeSet, RadarSignature, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(USignatureAttributeSet, InfraredSignature, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(USignatureAttributeSet, LidarSignature, COND_None, REPNOTIFY_OnChanged);
}

void USignatureAttributeSet::OnRep_RadarSignature(const FGameplayAttributeData& OldRadarSignature)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USignatureAttributeSet, RadarSignature, OldRadarSignature);
}

void USignatureAttributeSet::OnRep_InfraredSignature(const FGameplayAttributeData& OldInfraredSignature)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USignatureAttributeSet, InfraredSignature, OldInfraredSignature);
}

void USignatureAttributeSet::OnRep_LidarSignature(const FGameplayAttributeData& OldLidarSignature)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USignatureAttributeSet, LidarSignature, OldLidarSignature);
}
