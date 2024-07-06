// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/ProgressIndicator.h"
#include "Structures/ProgressIndication.h"

UStructureIndication* UProgressIndicator::GetIndication() const
{
	return Indication;
}
