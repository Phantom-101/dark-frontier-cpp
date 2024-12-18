// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/HullIndication.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"

float UHullIndication::GetHullPercent() const
{
	UStructureGameplay* Gameplay = Structure->GetGameplay();
	return Gameplay->GetHull() / Gameplay->GetMaxHull();
}
