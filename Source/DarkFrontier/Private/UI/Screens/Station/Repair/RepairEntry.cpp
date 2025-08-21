// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Repair/RepairEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Game/UniverseGameMode.h"
#include "Libraries/Math.h"
#include "Libraries/TradeFunctionLibrary.h"
#include "Structures/StructurePart.h"

void URepairEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Part = Cast<AStructurePart>(ListItemObject);
}

void URepairEntry::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();
	Part = nullptr;
}

void URepairEntry::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	GUARD(IsValid(Part));
	NameText->SetText(FText::FromString(Part->GetActorNameOrLabel()));
	const float Condition = UMath::DivTo1(Part->GetPartHealth(), Part->GetPartMaxHealth());
	ConditionText->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), Condition * 100)));
	const UTradeParameters* Parameters = GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();
	const float Cost = UTradeFunctionLibrary::GetPartRepairPrice(Part->GetPartMaxHealth() - Part->GetPartHealth(), Parameters);
	CostText->SetText(FText::FromString(FString::Printf(TEXT("%.0f C"), Cost)));
}
