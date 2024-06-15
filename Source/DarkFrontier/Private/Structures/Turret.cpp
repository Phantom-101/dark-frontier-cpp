// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Structures/FiringPoint.h"
#include "Structures/Structure.h"
#include "Structures/StructureDamage.h"
#include "Structures/TurretPayload.h"
#include "UI/Screens/GameUI/TurretAbilityProxy.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UFiringPoint>(FiringPoints);
}

void ATurret::OnRegistered()
{
	Super::OnRegistered();

	AbilityHandle = OwningStructure->GiveAbility(AbilityClass);
}

void ATurret::OnUnRegistered()
{
	Super::OnUnRegistered();

	if(AbilityHandle.IsValid())
	{
		OwningStructure->ClearAbility(AbilityHandle);
		AbilityHandle = FGameplayAbilitySpecHandle();
	}
}

FStructureDamage ATurret::GetDamage()
{
	return FStructureDamage();
}

void ATurret::ActivateAll()
{
	if(!IsValid(GetOwningStructure()->GetTarget())) return;
	
	for(UFiringPoint* FiringPoint : FiringPoints)
	{
		Activate(FiringPoint);
	}
	OnActivatedAll();
}

void ATurret::OnActivatedAll()
{
}

void ATurret::Activate(UFiringPoint* FiringPoint)
{
	if(!IsValid(GetOwningStructure()->GetTarget())) return;
	
	if(GetOwningStructure()->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle))
	{
		OnActivated(FiringPoint);
	}
}

void ATurret::OnActivated(UFiringPoint* FiringPoint)
{
	UTurretPayload* Payload = NewObject<UTurretPayload>(this);
	Payload->Damage = GetDamage();
	Payload->FiringPoint = FiringPoint;
	Payload->Target = GetOwningStructure()->GetTarget();
	SendPayload(Payload);
}

void ATurret::SendPayload(UObject* PayloadObject)
{
	FGameplayEventData Payload;
	Payload.Instigator = GetOwningStructure();
	Payload.OptionalObject = PayloadObject;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningStructure(), PayloadEventTag, Payload);
}

void ATurret::AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups)
{
	Super::AddAbilitiesToProxyGroups(ProxyGroups);

	UTurretAbilityProxy* Proxy = NewObject<UTurretAbilityProxy>();
	Proxy->Turret = this;
	AddAbilityToProxyGroups(ProxyGroups, AbilityClass, Proxy);
}

void ATurret::TryActivate()
{
}

float ATurret::GetAbilityArcLength()
{
	return 1;
}
