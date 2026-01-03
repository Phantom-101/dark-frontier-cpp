// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"

bool ATurret::CanActivate(UTargetable* InTarget) const
{
	return true;
}

void ATurret::TryActivate(UTargetable* InTarget)
{
	if(CanActivate(InTarget))
	{
		OnActivate(InTarget);
	}
}

void ATurret::OnActivate(UTargetable* InTarget)
{
}
