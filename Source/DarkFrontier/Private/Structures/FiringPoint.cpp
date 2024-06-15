// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/FiringPoint.h"
#include "Structures/Turret.h"

void UFiringPoint::BeginPlay()
{
	Super::BeginPlay();

	OwningTurret = GetOwner<ATurret>();
}

ATurret* UFiringPoint::GetOwningTurret() const
{
	return OwningTurret;
}
