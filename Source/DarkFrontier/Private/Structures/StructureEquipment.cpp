// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureEquipment.h"

AStructureEquipment::AStructureEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStructureEquipment::BeginPlay()
{
	Super::BeginPlay();
}

void AStructureEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

