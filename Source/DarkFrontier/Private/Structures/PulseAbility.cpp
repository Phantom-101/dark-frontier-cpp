// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Gameplay/Tasks/HitscanTask.h"
#include "Structures/HitscanResult.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructurePart.h"
#include "Structures/TurretPayload.h"
#include "Structures/TurretSource.h"
#include "Structures/Indications/TimerIndication.h"

void UPulseAbility::OnActivate(UTurretPayload* Payload)
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
	IgnoredActors.Append(CurrentPayload->Instigator->GetParts());
	
	UHitscanTask* HitscanTask = UHitscanTask::New(this, CurrentPayload->Source->GetComponentLocation(), CurrentPayload->Target->GetActorLocation(), TraceChannel, IgnoredActors);
	HitscanTask->Activate();

	if(IsValid(HitscanTask->HitPart))
	{
		UHitscanResult* Result = NewObject<UHitscanResult>();
		Result->Payload = CurrentPayload;
		Result->HitPart = HitscanTask->HitPart;
		Result->HitResult = HitscanTask->HitResult;

		UStructureAbilitySystemComponent* Comp = Cast<UStructureAbilitySystemComponent>(Result->Payload->Instigator->GetAbilitySystemComponent());
		if(Comp)
		{
			FGameplayCueParameters Parameters;
			Parameters.Instigator = Result->Payload->Instigator;
			Parameters.SourceObject = Result;
			Parameters.EffectContext.AddHitResult(Result->HitResult);
			Comp->ExecuteGameplayCueLocal(CueTag, Parameters);
		}
	}
}
