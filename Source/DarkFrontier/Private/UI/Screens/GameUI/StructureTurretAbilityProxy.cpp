// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureTurretAbilityProxy.h"
#include "Structures/StructureTurret.h"

FGameplayAbilitySpecHandle UStructureTurretAbilityProxy::GetAbilityHandle()
{
	return AbilityHandle;
}

float UStructureTurretAbilityProxy::GetArcLength()
{
	return Turret->GetAbilityArcLength();
}
