// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/ShieldIndication.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"

float UShieldIndication::GetShieldPercent() const
{
	// TODO replace with actual shield integrity, this shows hull rn just to get the compile working
	const UIntegrityAttributeSet* IntegrityAttributes = Structure->GetGameplay()->GetIntegrityAttributes();
	return IntegrityAttributes->GetIntegrity() / IntegrityAttributes->GetMaxIntegrity();
}
