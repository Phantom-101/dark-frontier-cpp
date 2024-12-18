// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseTurret.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DamageEvents.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureIndices.h"
#include "Structures/Damage/StructureDamageType.h"
#include "Structures/Indications/TimerIndication.h"
#include "UI/Screens/GameUI/PulseTurretControl.h"

APulseTurret::APulseTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool APulseTurret::CanActivate()
{
	return IsValid(OwningStructure->GetTarget()) && OwningStructure->GetGameplay()->GetEnergy() >= EnergyCost;
}

void APulseTurret::OnActivate()
{
	// Apply energy cost
	UStructureGameplay* Gameplay = OwningStructure->GetGameplay();
	Gameplay->SetEnergy(Gameplay->GetEnergy() - EnergyCost);

	// Save target
	SavedTarget = OwningStructure->GetTarget();

	// Setup attack indication
	UTimerIndication* Indication = Cast<UTimerIndication>(OwningStructure->AddIndication(UTimerIndication::StaticClass()));
	Indication->Init(Delay);

	// Apply damage after delay is completed
	GetWorldTimerManager().SetTimer(DelayHandle, this, &APulseTurret::OnDelayComplete, Delay);
}

UStructurePartControl* APulseTurret::CreateControl(UWidget* WidgetOwner)
{
	UPulseTurretControl* Control = CreateWidget<UPulseTurretControl>(WidgetOwner, ControlClass);
	Control->Turret = this;
	return Control;
}

void APulseTurret::OnDelayComplete()
{
	if(!IsValid(SavedTarget))
	{
		return;
	}

	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = SavedTarget->GetActorLocation();

	// Ignore owning structure and its parts in the line trace
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(OwningStructure);
	IgnoredActors.Append(OwningStructure->GetIndices()->GetParts());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, TraceChannel, QueryParams);

	// Apply damage sequentially to each target hit by the line trace
	float DamageRemaining = DamageAmount;
	for(const FHitResult& HitResult : HitResults)
	{
		FVector Direction = EndLocation - StartLocation;
		Direction.Normalize();
		
		const FPointDamageEvent Event = FPointDamageEvent(DamageRemaining, HitResult, Direction, DamageType.Get());
		DamageRemaining -= HitResult.GetActor()->TakeDamage(DamageRemaining, Event, OwningStructure->GetController(), this);

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

		// When all damage has been dealt, draw line to latest damaged target
		if(DamageRemaining <= 0 && IsValid(BeamSystem))
		{
			UNiagaraComponent* BeamComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BeamSystem, FVector::ZeroVector);
			BeamComponent->SetVariableVec3(FName("Beam Start"), StartLocation);
			BeamComponent->SetVariableVec3(FName("Beam End"), HitResult.Location);
			return;
		}
	}
	
	// Damage was not fully depleted, draw line to end location
	if(IsValid(BeamSystem))
	{
		UNiagaraComponent* BeamComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BeamSystem, FVector::ZeroVector);
		BeamComponent->SetVariableVec3(FName("Beam Start"), StartLocation);
		BeamComponent->SetVariableVec3(FName("Beam End"), EndLocation);
	}
}
