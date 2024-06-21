// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/HitscanAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Structures/HitscanResult.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/TurretPayload.h"

void UHitscanAbility::Activate(UTurretPayload* Payload)
{
	Super::Activate(Payload);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Payload->Instigator);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Payload->SourceTransform->GetComponentLocation(), Payload->Target->GetActorLocation(), TraceChannel, QueryParams);

	AStructurePart* HitPart = Cast<AStructurePart>(Hit.GetActor());

	if(!IsValid(HitPart))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	if(CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		UHitscanResult* Result = NewObject<UHitscanResult>();
		Result->Payload = Payload;
		Result->HitPart = HitPart;
		Result->Hit = Hit;
		OnHit(Result);
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UHitscanAbility::OnHit(UHitscanResult* Result)
{
}
