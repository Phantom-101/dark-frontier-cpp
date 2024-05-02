// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureTurretAbility.h"

#include "Log.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Structures/FiringPoint.h"
#include "Structures/StructureDamage.h"
#include "Structures/StructureTurret.h"

void UStructureTurretAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if(CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag);
		WaitEventTask->EventReceived.AddDynamic(this, &UStructureTurretAbility::HandleEventDataReceived);
		WaitEventTask->Activate();
	}
	else
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UStructureTurretAbility::HandleEventDataReceived(FGameplayEventData Payload)
{
	WaitEventTask->EventReceived.Clear();
	
	const AStructureTurret* Turret = Cast<AStructureTurret>(Payload.OptionalObject);
	UFiringPoint* FiringPoint = Cast<UFiringPoint>(Payload.OptionalObject2);
	FStructureDamage Damage = Turret->GetDamage();

	const FGameplayEffectSpecHandle EffectHandle = MakeOutgoingGameplayEffectSpec(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectClass, 1);
	Damage.SetMagnitudes(DamageTags, EffectHandle);
	FActiveGameplayEffectHandle _ = ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectHandle);
}
