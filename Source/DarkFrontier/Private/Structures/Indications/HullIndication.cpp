// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/HullIndication.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"

float UHullIndication::GetHullPercent() const
{
	const UIntegrityAttributeSet* IntegrityAttributes = Structure->GetGameplay()->GetIntegrityAttributes();
	return IntegrityAttributes->GetIntegrity() / IntegrityAttributes->GetMaxIntegrity();
}
