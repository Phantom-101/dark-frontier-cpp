// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogPropertyEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Libraries/Math.h"
#include "Sectors/Sector.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLocation.h"
#include "UI/Widgets/Visuals/FillBar.h"

void ULogPropertyEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Structure = Cast<AStructure>(ListItemObject);
}

void ULogPropertyEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Structure));

	NameText->SetText(FText::FromString(FString::Printf(TEXT("\"%s\" (%s)"), *Structure->GetActorNameOrLabel(), *Structure->GetLocation()->GetSector()->GetActorNameOrLabel())));

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	ShieldBar->FillHorizontal(0, UMath::DivTo0(Gameplay->GetShield(), Gameplay->GetMaxShield()));
	HullBar->FillHorizontal(0, UMath::DivTo0(Gameplay->GetHull(), Gameplay->GetMaxHull()));
}
