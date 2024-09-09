// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/ShieldIndication.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"

float UShieldIndication::GetShieldPercent() const
{
	return Structure->GetGameplay()->GetShield() / Structure->GetGameplay()->GetMaxShield();
}
