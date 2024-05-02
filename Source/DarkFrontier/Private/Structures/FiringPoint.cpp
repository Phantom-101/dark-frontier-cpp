// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/FiringPoint.h"
#include "Structures/StructureTurret.h"

void UFiringPoint::BeginPlay()
{
	Super::BeginPlay();

	OwningTurret = GetOwner<AStructureTurret>();
}

AStructureTurret* UFiringPoint::GetTurret() const
{
	return OwningTurret;
}
