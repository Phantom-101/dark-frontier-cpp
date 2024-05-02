// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureTurret.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureTurretAbilityProxy.h"

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

void AStructureTurret::AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups)
{
	Super::AddAbilitiesToProxyGroups(ProxyGroups);

	UStructureTurretAbilityProxy* Proxy = NewObject<UStructureTurretAbilityProxy>();
	Proxy->Turret = this;
	Proxy->AbilityHandle = TurretAbilityHandle;
	AddAbilityToProxyGroups(ProxyGroups, TurretAbilityClass, Proxy);
}

float AStructureTurret::GetAbilityArcLength()
{
	return 1;
}
