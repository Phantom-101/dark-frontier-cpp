// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/SpeedIndication.h"
#include "Structures/Structure.h"

float USpeedIndication::GetSpeed() const
{
	return Structure->GetVelocity().Length();
}
