// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Net/UnrealNetwork.h"

void ULayoutAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULayoutAttributeSet, MaxUpkeep, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(ULayoutAttributeSet, Upkeep, COND_None, REPNOTIFY_OnChanged);
}

void ULayoutAttributeSet::OnRep_MaxUpkeep(const FGameplayAttributeData& OldMaxUpkeep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULayoutAttributeSet, MaxUpkeep, OldMaxUpkeep);
}

void ULayoutAttributeSet::OnRep_Upkeep(const FGameplayAttributeData& OldUpkeep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULayoutAttributeSet, Upkeep, OldUpkeep);
}
