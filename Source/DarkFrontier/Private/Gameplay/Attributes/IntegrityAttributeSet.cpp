// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UIntegrityAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetIntegrityAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxIntegrity());
	}
}

void UIntegrityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UIntegrityAttributeSet, MaxIntegrity, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UIntegrityAttributeSet, Integrity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UIntegrityAttributeSet, Regeneration, COND_None, REPNOTIFY_OnChanged);
}

void UIntegrityAttributeSet::OnRep_MaxIntegrity(const FGameplayAttributeData& OldMaxIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIntegrityAttributeSet, MaxIntegrity, OldMaxIntegrity);
}

void UIntegrityAttributeSet::OnRep_Integrity(const FGameplayAttributeData& OldIntegrity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIntegrityAttributeSet, Integrity, OldIntegrity);
}

void UIntegrityAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIntegrityAttributeSet, Regeneration, OldRegeneration);
}
