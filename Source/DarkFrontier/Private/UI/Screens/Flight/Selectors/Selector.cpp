// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/Selector.h"
#include "CommonButtonBase.h"
#include "Macros.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Objects/Targetable.h"
#include "Structures/StructureController.h"

void USelector::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	PanelSlot->SetAlignment(FVector2D(0.5));
	PanelSlot->SetSize(FVector2D(100));

	SelectButton->OnClicked().AddUObject(this, &USelector::Select);
}

void USelector::Init(const TScriptInterface<ITargetable>& InTarget)
{
	Target = InTarget;
}

void USelector::UpdateSelector(const FGeometry& CanvasGeometry)
{
	GUARD(IsValid(Target.GetObject()));

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	FVector2D ScreenPos;
	GetOwningPlayer()->ProjectWorldLocationToScreen(Target->GetTargetLocation(), ScreenPos);
	FVector2D LocalPos;
	USlateBlueprintLibrary::ScreenToWidgetLocal(this, CanvasGeometry, ScreenPos, LocalPos);
	PanelSlot->SetPosition(LocalPos);
	
	SetRenderScale(Target->IsSelectedByPlayer() ? FVector2D(1.5) : FVector2D(1));
	
	SetVisibility(Target->ShouldShowSelector() ? ESlateVisibility::SelfHitTestInvisible: ESlateVisibility::Collapsed);
}

void USelector::Select() const
{
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Target.GetObject()) && IsValid(Controller))
	{
		Controller->SetSelectTarget(Target);
	}
}
