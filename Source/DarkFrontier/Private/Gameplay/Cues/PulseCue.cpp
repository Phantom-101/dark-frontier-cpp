// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Cues/PulseCue.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Structures/HitscanResult.h"
#include "Structures/TurretPayload.h"
#include "Structures/TurretSource.h"

bool APulseCue::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	const UHitscanResult* Result = Cast<const UHitscanResult>(Parameters.SourceObject);

	BeamComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BeamSystem, FVector::ZeroVector);
	BeamComponent->SetNiagaraVariableVec3("Beam Start", Result->Payload->Source->GetComponentLocation());
	BeamComponent->SetNiagaraVariableVec3("Beam End", Result->HitResult.Location);
	
	return false;
}
