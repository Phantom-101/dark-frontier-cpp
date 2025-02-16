// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/StructureEntry.h"
#include "CommonTextBlock.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UStructureEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UStructureGameplay* Gameplay = Structure->GetGameplay();
	ShieldBar->SetFill(FVector2D(Gameplay->GetShield() / Gameplay->GetMaxShield(), 1));
	HullBar->SetFill(FVector2D(Gameplay->GetHull() / Gameplay->GetMaxHull(), 1));
}

void UStructureEntry::Init(AStructure* InStructure)
{
	Structure = InStructure;
	
	NameText->SetText(FText::FromString(Structure->GetName()));
}
