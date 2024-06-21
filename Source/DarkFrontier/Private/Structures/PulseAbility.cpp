// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseAbility.h"
#include "Structures/HitscanResult.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/TurretPayload.h"

void UPulseAbility::OnHit(UHitscanResult* Result)
{
	Super::OnHit(Result);

	UStructureAbilitySystemComponent* Comp = Cast<UStructureAbilitySystemComponent>(Result->Payload->Instigator->GetAbilitySystemComponent());
	if(Comp)
	{
		FGameplayCueParameters Parameters;
		Parameters.Instigator = Result->Payload->Instigator;
		Parameters.SourceObject = Result;
		Parameters.EffectContext.AddHitResult(Result->Hit);
		Comp->ExecuteGameplayCueLocal(CueTag, Parameters);
	}
}
