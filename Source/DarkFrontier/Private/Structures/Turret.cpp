// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"

bool ATurret::CanActivate(const TScriptInterface<ITargetable>& Target)
{
	return true;
}

void ATurret::TryActivate(const TScriptInterface<ITargetable>& Target)
{
	if(!CanActivate(Target))
	{
		return;
	}

	OnActivate(Target);
}

void ATurret::OnActivate(const TScriptInterface<ITargetable>& Target)
{
}
