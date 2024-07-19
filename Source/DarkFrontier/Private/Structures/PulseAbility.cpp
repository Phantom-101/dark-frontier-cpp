// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Gameplay/Tasks/HitscanTask.h"
#include "Structures/HitscanIndication.h"
#include "Structures/HitscanResult.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructurePart.h"
#include "Structures/TurretPayload.h"
#include "Structures/TurretSource.h"

void UPulseAbility::OnActivate(UTurretPayload* Payload)
{
	Super::OnActivate(Payload);

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Payload->Instigator);
	for(AStructurePart* Part : Payload->Instigator->GetParts())
	{
		IgnoredActors.Add(Part);
	}
	
	UHitscanTask* HitscanTask = UHitscanTask::New(this, Payload->Source->GetComponentLocation(), Payload->Target->GetActorLocation(), TraceChannel, IgnoredActors);
	HitscanTask->Activate();

	if(!IsValid(HitscanTask->HitPart))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	if(CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		UHitscanIndication* Indication = Cast<UHitscanIndication>(Payload->Instigator->AddIndication(IndicationClass));
		Indication->MaxTime = Delay;
		Indication->CurrentTime = Delay;

		CurrentPayload = Payload;
		CurrentTask = HitscanTask;
		
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
	UHitscanResult* Result = NewObject<UHitscanResult>();
	Result->Payload = CurrentPayload;
	Result->HitPart = CurrentTask->HitPart;
	Result->HitResult = CurrentTask->HitResult;

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
