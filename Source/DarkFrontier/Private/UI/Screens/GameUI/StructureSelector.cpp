// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureSelector.h"
#include "CommonButtonBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "Structures/Structure.h"
#include "Structures/StructureIndication.h"
#include "UI/Screens/GameUI/StructureIndicator.h"

void UStructureSelector::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	PanelSlot->SetAlignment(FVector2D(0.5, 0.5));

	SelectorButton->OnClicked().Clear();
	SelectorButton->OnClicked().AddUObject<UStructureSelector>(this, &UStructureSelector::OnClicked);
}

void UStructureSelector::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	// Set position
	FVector2D ScreenPos;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Controller, Target->GetActorLocation(), ScreenPos, false);
	PanelSlot->SetPosition(ScreenPos);

	// Set size
	PanelSlot->SetSize(FVector2D(100, 100));

	// Set visibility
	AStructure* Player = Cast<AStructure>(Controller->GetPawn());
	if(IsValid(Player))
	{
		if(Target == Player)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}

	// Create indicators
	TArray<UStructureIndication*> Existing;
	TArray<UWidget*> ToRemove;
	for(UWidget* Widget : IndicatorOverlay->GetAllChildren())
	{
		const UStructureIndicator* Indicator = Cast<UStructureIndicator>(Widget);
		if(IsValid(Indicator) && IsValid(Indicator->GetIndication()))
		{
			Existing.Add(Indicator->GetIndication());
		}
		else
		{
			ToRemove.Add(Widget);
		}
	}

	for(UWidget* Widget : ToRemove)
	{
		IndicatorOverlay->RemoveChild(Widget);
	}

	for(UStructureIndication* Indication : Target->GetIndications())
	{
		if(!Existing.Contains(Indication))
		{
			IndicatorOverlay->AddChildToOverlay(Indication->CreateIndicator(this));
		}
	}
}

void UStructureSelector::OnClicked() const
{
	AStructure* Player = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(IsValid(Target) && IsValid(Player))
	{
		Player->SetTarget(Target);
	}
}
