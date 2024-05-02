// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureTurret.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Items/Ammo.h"
#include "Structures/FiringPoint.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureTurretAbilityProxy.h"

void AStructureTurret::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UFiringPoint>(FiringPoints);
}

void AStructureTurret::OnRegistered()
{
	Super::OnRegistered();

	TurretAbilityHandle = OwningStructure->GiveAbility(TurretAbilityClass);
}

void AStructureTurret::OnUnRegistered()
{
	Super::OnUnRegistered();

	if(TurretAbilityHandle.IsValid())
	{
		OwningStructure->ClearAbility(TurretAbilityHandle);
		TurretAbilityHandle = FGameplayAbilitySpecHandle();
	}
}

FStructureDamage AStructureTurret::GetDamage() const
{
	if(CurrentAmmoType == nullptr)
	{
		if(RequiresAmmo)
		{
			return FStructureDamage();
		}

		return BaseDamage;
	}

	return CurrentAmmoType->BaseDamage.Scale(AmmoDamageMultiplier);
}

float AStructureTurret::GetCooldown() const
{
	if(CurrentAmmoType == nullptr)
	{
		return Cooldown;
	}

	return Cooldown * CurrentAmmoType->TurretCooldownMultiplier;
}

TArray<UAmmo*> AStructureTurret::GetAmmoTypes()
{
	return AmmoTypes;
}

UAmmo* AStructureTurret::GetCurrentAmmoType() const
{
	return CurrentAmmoType;
}

bool AStructureTurret::TrySetCurrentAmmoType(UAmmo* AmmoType)
{
	if(AmmoType == nullptr && RequiresAmmo)
	{
		return false;
	}
	
	if(AmmoType != nullptr && !AmmoTypes.Contains(AmmoType))
	{
		return false;
	}

	CurrentAmmoType = AmmoType;
	return true;
}

void AStructureTurret::AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups)
{
	Super::AddAbilitiesToProxyGroups(ProxyGroups);

	UStructureTurretAbilityProxy* Proxy = NewObject<UStructureTurretAbilityProxy>();
	Proxy->Turret = this;
	AddAbilityToProxyGroups(ProxyGroups, TurretAbilityClass, Proxy);
}

void AStructureTurret::TryActivate()
{
	// todo consider ammo here
	for(UFiringPoint* FiringPoint : FiringPoints)
	{
		if(GetOwningStructure()->GetAbilitySystemComponent()->TryActivateAbility(TurretAbilityHandle))
		{
			FGameplayEventData Payload;
			Payload.Instigator = GetOwningStructure();
			Payload.OptionalObject = this;
			Payload.OptionalObject2 = FiringPoint;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningStructure(), EventTag, Payload);
		}
	}
}

float AStructureTurret::GetAbilityArcLength()
{
	return 1;
}
