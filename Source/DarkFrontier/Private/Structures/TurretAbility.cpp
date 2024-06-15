// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TurretAbility.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Structures/Turret.h"
#include "Structures/TurretPayload.h"
#include "Structures/FiringPoint.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbilitySystemComponent.h"

void UTurretAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PayloadEventTag);
	WaitEventTask->EventReceived.Clear();
	WaitEventTask->EventReceived.AddDynamic(this, &UTurretAbility::HandleEventDataReceived);
	WaitEventTask->Activate();
}

void UTurretAbility::HandleEventDataReceived(FGameplayEventData Payload)
{
	WaitEventTask->EventReceived.Clear();

	const UTurretPayload* PayloadObject = Cast<UTurretPayload>(Payload.OptionalObject);

	AStructure* Instigator = PayloadObject->FiringPoint->GetOwningTurret()->GetOwningStructure();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Instigator);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, PayloadObject->FiringPoint->GetComponentLocation(), PayloadObject->Target->GetActorLocation(), TraceChannel, QueryParams);

	AStructurePart* HitPart = Cast<AStructurePart>(Hit.GetActor());

	if(!IsValid(HitPart))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	if(CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		// todo call damage function here

		UStructureAbilitySystemComponent* ASC = Cast<UStructureAbilitySystemComponent>(Instigator->GetAbilitySystemComponent());

		FGameplayCueParameters Parameters;
		Parameters.Instigator = Instigator;
		Parameters.EffectContext.AddHitResult(Hit);
		ASC->ExecuteGameplayCueLocal(CueTag, Parameters);
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}
