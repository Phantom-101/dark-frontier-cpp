// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Layout/InfoLayoutEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Libraries/Math.h"
#include "Structures/StructurePart.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UInfoLayoutEntry::Init(AStructurePart* InPart)
{
	Part = InPart;
}

void UInfoLayoutEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<AStructurePart>(ListItemObject));
}

void UInfoLayoutEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Part));

	NameText->SetText(FText::FromString(Part->GetActorNameOrLabel()));
	ConditionBar->FillHorizontal(0, UMath::DivTo0(Part->GetPartHealth(), Part->GetPartMaxHealth()));
}
