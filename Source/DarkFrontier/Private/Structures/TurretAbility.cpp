// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TurretAbility.h"
#include "Log.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/TurretPayload.h"

void UTurretAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PayloadTag);
	UE_LOG(LogDarkFrontier, Log, TEXT("New wait event task has %d listeners"), WaitEventTask->EventReceived.GetAllObjects().Num());
	//WaitEventTask->EventReceived.Clear();
	WaitEventTask->EventReceived.AddDynamic(this, &UTurretAbility::HandlePayloadReceived);
	WaitEventTask->Activate();
}

void UTurretAbility::Activate(UTurretPayload* Payload)
{
}

void UTurretAbility::HandlePayloadReceived(const FGameplayEventData Payload)
{
	UTurretPayload* Obj = Cast<UTurretPayload>(Payload.OptionalObject);
	if(Obj != nullptr)
	{
		Activate(Obj);
	}
}
