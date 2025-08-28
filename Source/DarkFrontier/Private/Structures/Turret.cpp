// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"

bool ATurret::CanActivate(const TScriptInterface<ITargetable>& InTarget) const
{
	return true;
}

void ATurret::TryActivate(const TScriptInterface<ITargetable>& InTarget)
{
	if(!CanActivate(InTarget))
	{
		return;
	}

	OnActivate(InTarget);
}

void ATurret::OnActivate(const TScriptInterface<ITargetable>& InTarget)
{
}
