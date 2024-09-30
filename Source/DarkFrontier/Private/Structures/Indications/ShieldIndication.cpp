// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/ShieldIndication.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"

float UShieldIndication::GetShieldPercent() const
{
	// TODO replace with actual shield integrity, this shows hull rn just to get the compile working
	UStructureGameplay* Gameplay = Structure->GetGameplay();
	return Gameplay->GetIntegrity() / Gameplay->GetMaxIntegrity();
}
