// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Layout/InfoLayoutTab.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/Info/InfoScreen.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UInfoLayoutTab::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Screen));

	const AStructure* Structure = Cast<AStructure>(Screen->GetActor());
	GUARD(IsValid(Structure));

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	EnergyField->SetContentFromString(FString::Printf(TEXT("%.1f+%.1f"), Gameplay->GetMaxEnergy(), Gameplay->GetEnergyRegeneration()));
	UpkeepField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Gameplay->GetUpkeep(), Gameplay->GetMaxUpkeep()));

	ListView->SetListItems<AStructurePart*>(Structure->GetLayout()->GetParts());
}
