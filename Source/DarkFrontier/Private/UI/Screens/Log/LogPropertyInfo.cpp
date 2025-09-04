// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogPropertyInfo.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Libraries/Math.h"
#include "Sectors/Sector.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLocation.h"
#include "UI/Widgets/Visuals/FillBar.h"
#include "UI/Widgets/Visuals/InfoField.h"

void ULogPropertyInfo::Init(AStructure* InStructure)
{
	Structure = InStructure;
}

void ULogPropertyInfo::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Structure));

	NameText->SetText(FText::FromString(Structure->GetActorNameOrLabel()));

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	ShieldBar->FillHorizontal(0, UMath::DivTo0(Gameplay->GetShield(), Gameplay->GetMaxShield()));
	HullBar->FillHorizontal(0, UMath::DivTo0(Gameplay->GetHull(), Gameplay->GetMaxHull()));

	SectorField->SetContentFromString(Structure->GetLocation()->GetSector()->GetActorNameOrLabel());
	PositionField->SetContentFromString(FString::Printf(TEXT("X: %.1f, Y: %.1f"), Structure->GetActorLocation().X, Structure->GetActorLocation().Y));

	OrderField->SetContentFromString("None");

	VolumeField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Structure->GetInventory()->GetTotalVolume(), Structure->GetInventory()->GetMaxVolume()));
	MassField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Structure->GetInventory()->GetTotalMass(), Structure->GetInventory()->GetMaxMass()));
}
