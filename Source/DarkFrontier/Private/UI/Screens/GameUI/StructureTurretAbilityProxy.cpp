// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureTurretAbilityProxy.h"
#include "Structures/StructureTurret.h"

void UStructureTurretAbilityProxy::TryActivate()
{
	Turret->TryActivate();
}

float UStructureTurretAbilityProxy::GetArcLength()
{
	return Turret->GetAbilityArcLength();
}
