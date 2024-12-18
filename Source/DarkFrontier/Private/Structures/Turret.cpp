// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"

bool ATurret::CanActivate()
{
	return true;
}

void ATurret::TryActivate()
{
	if(!CanActivate())
	{
		return;
	}

	OnActivate();
}

void ATurret::OnActivate()
{
}
