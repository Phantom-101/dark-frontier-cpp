// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseAbility.h"
#include "Gameplay/Tasks/HitscanTask.h"
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
		UHitscanResult* Result = NewObject<UHitscanResult>();
		Result->Payload = Payload;
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
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}
