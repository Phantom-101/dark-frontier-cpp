// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/TurretAbilityProxy.h"
#include "Structures/Turret.h"

void UTurretAbilityProxy::TryActivate()
{
	Turret->TryActivate();
}

float UTurretAbilityProxy::GetArcLength()
{
	return Turret->GetAbilityArcLength();
}
