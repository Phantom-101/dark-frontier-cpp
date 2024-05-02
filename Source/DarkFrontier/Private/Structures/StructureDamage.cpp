// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDamage.h"

FStructureDamage::FStructureDamage()
{
}

FStructureDamage::FStructureDamage(const float InKinetic, const float InExplosive, const float InBeam, const float InField)
{
	Kinetic = abs(InKinetic);
	Explosive = abs(InExplosive);
	Beam = abs(InBeam);
	Field = abs(InField);
}

float FStructureDamage::Sum() const
{
	return Kinetic + Explosive + Beam + Field;
}

FStructureDamage FStructureDamage::Scale(const float InFactor) const
{
	return FStructureDamage(
		Kinetic * InFactor,
		Explosive * InFactor,
		Beam * InFactor,
		Field * InFactor
	);
}
