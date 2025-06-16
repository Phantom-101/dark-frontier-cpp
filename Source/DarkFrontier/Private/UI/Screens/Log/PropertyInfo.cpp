// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/PropertyInfo.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/Log/StructureEntry.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UPropertyInfo::Init(AStructure* Structure) const
{
	Header->Init(Structure);
	PositionField->SetContentFromString(FString::Printf(TEXT("X: %.1f, Y: %.1f"), Structure->GetActorLocation().X, Structure->GetActorLocation().Y));
	OrderField->SetContentFromString("None");
	VolumeField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Structure->GetInventory()->GetTotalVolume(), Structure->GetInventory()->GetMaxVolume()));
	MassField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Structure->GetInventory()->GetTotalMass(), Structure->GetInventory()->GetMaxMass()));
}
