// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Engine/DamageEvents.h"
#include "Gameplay/Tasks/HitscanTask.h"
#include "Structures/HitscanResult.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureIndices.h"
#include "Structures/Turret.h"
#include "Structures/TurretPayload.h"
#include "Structures/TurretSource.h"
#include "Structures/Damage/StructureDamageType.h"
#include "Structures/Indications/TimerIndication.h"

void UPulseAbility::OnActivate(const UTurretPayload* Payload)
{
	Super::OnActivate(Payload);

	CurrentPayload = Payload;

	if(CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		// Setup attack indication
		UTimerIndication* Indication = Cast<UTimerIndication>(Payload->Instigator->AddIndication(IndicationClass));
		Indication->Init(Delay);

		// Wait to perform raycast and apply damage
		UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, Delay);
		DelayTask->OnFinish.AddDynamic(this, &UPulseAbility::OnDelayFinish);
		DelayTask->Activate();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UPulseAbility::OnDelayFinish()
{
	if(!IsValid(CurrentPayload->Instigator) || !IsValid(CurrentPayload->Target))
	{
		return;
	}
	
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(CurrentPayload->Instigator);
	IgnoredActors.Append(CurrentPayload->Instigator->GetIndices()->GetParts());

	const FVector Start = CurrentPayload->Source->GetComponentLocation();
	const FVector End = CurrentPayload->Target->GetActorLocation();
	UHitscanTask* HitscanTask = UHitscanTask::New(this, Start, End, TraceChannel, IgnoredActors);
	HitscanTask->Activate();

	float DamageRemaining = DamageAmount;
	for(const FHitResult& HitResult : HitscanTask->HitResults)
	{
		FVector Direction = End - Start;
		Direction.Normalize();
		
		const FPointDamageEvent Event = FPointDamageEvent(DamageRemaining, HitResult, Direction, DamageType);
		AController* Instigator = CurrentPayload->Instigator->GetController();
		AActor* Causer = CurrentPayload->Turret;
		
		DamageRemaining -= HitResult.GetActor()->TakeDamage(DamageRemaining, Event, Instigator, Causer);

		/*
		UStructureAbilitySystemComponent* Comp = Cast<UStructureAbilitySystemComponent>(Result->Payload->Instigator->GetAbilitySystemComponent());
		if(Comp)
		{
			FGameplayCueParameters Parameters;
			Parameters.Instigator = Result->Payload->Instigator;
			Parameters.SourceObject = Result;
			Parameters.EffectContext.AddHitResult(Result->HitResult);
			Comp->ExecuteGameplayCueLocal(CueTag, Parameters);
		}
		 */
	}
}
