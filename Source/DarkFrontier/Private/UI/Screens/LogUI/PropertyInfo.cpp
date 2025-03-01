// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/PropertyInfo.h"
#include "Items/Inventory.h"
#include "Structures/Structure.h"
#include "UI/Screens/LogUI/StructureEntry.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UPropertyInfo::Init(AStructure* Structure) const
{
	Header->Init(Structure);
	PositionField->SetContentFromString(FString::Printf(TEXT("X: %f, Y: %f"), Structure->GetActorLocation().X, Structure->GetActorLocation().Y));
	OrderField->SetContentFromString("None");
	VolumeField->SetContentFromString(FString::Printf(TEXT("%f/%f"), Structure->GetInventory()->GetTotalVolume(), Structure->GetInventory()->GetMaxVolume()));
	MassField->SetContentFromString(FString::Printf(TEXT("%f/%f"), Structure->GetInventory()->GetTotalMass(), Structure->GetInventory()->GetMaxMass()));
}
