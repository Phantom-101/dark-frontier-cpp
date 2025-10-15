// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Overview/StructureOverview.h"
#include "Macros.h"
#include "Factions/Faction.h"
#include "Libraries/Math.h"
#include "Sectors/Sector.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureInventory.h"
#include "UI/Widgets/Visuals/FillBar.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UStructureOverview::Init(AStructure* InStructure)
{
	Structure = InStructure;
}

void UStructureOverview::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Structure));

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	const float ShieldCondition = UMath::DivTo0(Gameplay->GetShield(), Gameplay->GetMaxShield());
	const float HullCondition = UMath::DivTo0(Gameplay->GetHull(), Gameplay->GetMaxHull());
	ShieldBar->FillHorizontal(0, ShieldCondition);
	HullBar->FillHorizontal(0, HullCondition);

	SectorField->SetContentFromString(Structure->GetSectorLocation()->GetSector()->GetActorNameOrLabel());
	PositionField->SetContentFromString(FString::Printf(TEXT("X: %.1f, Y: %.1f"), Structure->GetActorLocation().X, Structure->GetActorLocation().Y));

	FactionField->SetContent(Structure->GetAffiliation()->GetFaction()->GetFactionName());
	OrderField->SetContentFromString("Unknown");

	const UStructureInventory* Inventory = Structure->GetInventory();
	VolumeField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Inventory->GetTotalVolume(), Inventory->GetMaxVolume()));
	MassField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Inventory->GetTotalMass(), Inventory->GetMaxMass()));
}
