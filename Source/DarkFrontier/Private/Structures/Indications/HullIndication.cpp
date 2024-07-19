// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/HullIndication.h"
#include "Structures/Structure.h"

float UHullIndication::GetHullPercent() const
{
	return Structure->GetHull() / Structure->GetMaxHull();
}
