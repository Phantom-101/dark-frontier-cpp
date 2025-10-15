// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Hangar/InfoHangarEntry.h"
#include "CommonTextBlock.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UInfoHangarEntry::Init(UStructureDock* InDock)
{
	Dock = InDock;
}

void UInfoHangarEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UStructureDock>(ListItemObject));
}

void UInfoHangarEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Dock));

	const AStructure* Docker = Dock->GetDocker();
	NameText->SetText(IsValid(Docker) ? FText::FromString(Docker->GetActorNameOrLabel()) : FText::FromString("None"));
	SizeField->SetContentFromString("Unlimited");
}
