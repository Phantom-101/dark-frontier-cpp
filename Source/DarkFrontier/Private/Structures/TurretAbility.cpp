// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TurretAbility.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Structures/TurretPayload.h"

void UTurretAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PayloadTag, nullptr, true);
	WaitEventTask->EventReceived.AddDynamic(this, &UTurretAbility::HandlePayloadReceived);
	WaitEventTask->Activate();
}

void UTurretAbility::OnActivate(const UTurretPayload* Payload)
{
}

void UTurretAbility::HandlePayloadReceived(const FGameplayEventData Payload)
{
	const UTurretPayload* Obj = Cast<UTurretPayload>(Payload.OptionalObject);
	if(Obj != nullptr)
	{
		OnActivate(Obj);
	}
}
