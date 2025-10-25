// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Hangar/InfoHangarTab.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"
#include "Structures/StructureLayout.h"
#include "UI/Screens/Info/InfoScreen.h"

bool UInfoHangarTab::IsRelevant(AActor* Actor) const
{
	return IsValid(Cast<AStructure>(Actor));
}

void UInfoHangarTab::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Screen));

	const AStructure* Structure = Cast<AStructure>(Screen->GetActor());
	GUARD(IsValid(Structure));

	ListView->SetListItems(Structure->GetLayout()->GetFacilities<UStructureDock>());
}
