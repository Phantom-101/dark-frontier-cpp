// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Station/Repair/RepairScreen.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "Factions/Faction.h"
#include "Game/UniverseGameMode.h"
#include "Input/CommonBoundActionButton.h"
#include "Libraries/Math.h"
#include "Libraries/TradeFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "UI/Widgets/Interaction/Stripe.h"
#include "UI/Widgets/Visuals/FillBar.h"

void URepairScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	UpdateStripes();

	const AStructure* Structure = GetWorld()->GetFirstPlayerController()->GetPawn<AStructure>();
	GUARD(IsValid(Structure));
	ListView->SetListItems(Structure->GetLayout()->GetParts());
}

void URepairScreen::RegisterBindings()
{
	Super::RegisterBindings();

	CloseButton->SetRepresentedAction(BindFunction<URepairScreen>(CloseAction, &URepairScreen::DeactivateWidget));
	ShieldButton->OnClicked().AddUObject(this, &URepairScreen::ToggleShield);
	HullButton->OnClicked().AddUObject(this, &URepairScreen::ToggleHull);
	SelectAllButton->SetRepresentedAction(BindFunction<URepairScreen>(SelectAllAction, &URepairScreen::SelectAll));
	DeselectAllButton->SetRepresentedAction(BindFunction<URepairScreen>(DeselectAllAction, &URepairScreen::DeselectAll));
	ConfirmButton->SetRepresentedAction(BindFunction<URepairScreen>(ConfirmAction, &URepairScreen::Confirm));
}

void URepairScreen::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const AStructure* Structure = GetWorld()->GetFirstPlayerController()->GetPawn<AStructure>();
	GUARD(IsValid(Structure));

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	const UTradeParameters* Parameters = GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();

	const float ShieldCondition = UMath::DivTo1(Gameplay->GetShield(), Gameplay->GetMaxShield());
	ShieldBar->FillHorizontal(0, ShieldCondition);
	ShieldConditionText->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), ShieldCondition * 100)));
	const float ShieldCost = UTradeFunctionLibrary::GetShieldRepairPrice(Gameplay->GetMaxShield() - Gameplay->GetShield(), Parameters);
	ShieldCostText->SetText(FText::FromString(FString::Printf(TEXT("%.0f C"), ShieldCost)));

	const float HullCondition = UMath::DivTo1(Gameplay->GetHull(), Gameplay->GetMaxHull());
	HullBar->FillHorizontal(0, HullCondition);
	HullConditionText->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), HullCondition * 100)));
	const float HullCost = UTradeFunctionLibrary::GetHullRepairPrice(Gameplay->GetMaxHull() - Gameplay->GetHull(), Parameters);
	HullCostText->SetText(FText::FromString(FString::Printf(TEXT("%.0f C"), HullCost)));

	CostText->SetText(FText::FromString(FString::Printf(TEXT("%.0f C"), GetTotalCost())));
}

void URepairScreen::UpdateStripes() const
{
	ShieldStripe->SetIsVisible(RepairShield);
	HullStripe->SetIsVisible(RepairHull);
}

void URepairScreen::ToggleShield()
{
	RepairShield = !RepairShield;
	UpdateStripes();
}

void URepairScreen::ToggleHull()
{
	RepairHull = !RepairHull;
	UpdateStripes();
}

void URepairScreen::SelectAll()
{
	const AStructure* Structure = GetWorld()->GetFirstPlayerController()->GetPawn<AStructure>();
	GUARD(IsValid(Structure));
	for(AStructurePart* Part : Structure->GetLayout()->GetParts())
	{
		ListView->SetItemSelection(Part, true);
	}
}

void URepairScreen::DeselectAll()
{
	ListView->ClearSelection();
}

float URepairScreen::GetTotalCost() const
{
	const AStructure* Structure = GetWorld()->GetFirstPlayerController()->GetPawn<AStructure>();
	GUARD_RETURN(IsValid(Structure), 0);
	
	TArray<AStructurePart*> Selected;
	TArray<UObject*> Objects;
	ListView->GetSelectedItems(Objects);
	for(UObject* Object : Objects)
	{
		if(Object->IsA<AStructurePart>())
		{
			Selected.Add(Cast<AStructurePart>(Object));
		}
	}

	const UStructureGameplay* Gameplay = Structure->GetGameplay();
	const UTradeParameters* Parameters = GetWorld()->GetAuthGameMode<AUniverseGameMode>()->GetTradeParameters();
	
	float TotalCost = 0;

	if(RepairShield)
	{
		TotalCost += UTradeFunctionLibrary::GetShieldRepairPrice(Gameplay->GetMaxShield() - Gameplay->GetShield(), Parameters);
	}

	if(RepairHull)
	{
		TotalCost += UTradeFunctionLibrary::GetHullRepairPrice(Gameplay->GetMaxHull() - Gameplay->GetHull(), Parameters);
	}
	
	for(const AStructurePart* Part : Selected)
	{
		TotalCost += UTradeFunctionLibrary::GetPartRepairPrice(Part->GetPartMaxHealth() - Part->GetPartHealth(), Parameters);
	}

	return TotalCost;
}

void URepairScreen::Confirm()
{
	const AStructure* Structure = GetWorld()->GetFirstPlayerController()->GetPawn<AStructure>();
	GUARD(IsValid(Structure));

	TArray<AStructurePart*> Selected;
	TArray<UObject*> Objects;
	ListView->GetSelectedItems(Objects);
	for(UObject* Object : Objects)
	{
		if(Object->IsA<AStructurePart>())
		{
			Selected.Add(Cast<AStructurePart>(Object));
		}
	}
	
	UStructureGameplay* Gameplay = Structure->GetGameplay();

	const float TotalCost = GetTotalCost();
	AFaction* Faction = Structure->GetOwningFaction();
	if(Faction->GetBalance() >= TotalCost)
	{
		Faction->ChangeBalance(-TotalCost);

		if(RepairShield)
		{
			Gameplay->SetShield(Gameplay->GetMaxShield());
		}

		if(RepairHull)
		{
			Gameplay->SetHull(Gameplay->GetMaxHull());
		}

		for(AStructurePart* Part : Selected)
		{
			Part->SetPartHealth(Part->GetPartMaxHealth());
		}
	}

	DeactivateWidget();
}
