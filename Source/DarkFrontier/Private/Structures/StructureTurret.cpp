// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureTurret.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureTurretAbilityProxy.h"

void AStructureTurret::OnRegistered()
{
	Super::OnRegistered();

	AbilityHandle = OwningStructure->GiveAbility(Ability);
}

void AStructureTurret::OnUnRegistered()
{
	Super::OnUnRegistered();

	if(AbilityHandle.IsValid())
	{
		OwningStructure->ClearAbility(AbilityHandle);
		AbilityHandle = FGameplayAbilitySpecHandle();
	}
}

void AStructureTurret::AddAbilitiesToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups)
{
	Super::AddAbilitiesToProxyGroups(ProxyGroups);

	UStructureTurretAbilityProxy* Proxy = NewObject<UStructureTurretAbilityProxy>();
	Proxy->Turret = this;
	Proxy->AbilityHandle = AbilityHandle;
	AddAbilityToProxyGroups(ProxyGroups, Ability, Proxy);
}

float AStructureTurret::GetAbilityArcLength()
{
	return 1;
}
