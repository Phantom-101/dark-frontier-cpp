// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/Selectors/StructureSelector.h"
#include "CommonButtonBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/Indicators/StructureIndicators.h"

void UStructureSelector::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	PanelSlot->SetAlignment(FVector2D(0.5));
	PanelSlot->SetSize(FVector2D(100));

	SelectorButton->OnClicked().AddUObject<UStructureSelector>(this, &UStructureSelector::HandleClick);
}

void UStructureSelector::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	FVector2D ScreenPos;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Controller, Target->GetActorLocation(), ScreenPos, false);
	PanelSlot->SetPosition(ScreenPos);
	
	SetRenderScale(Target->IsSelected() ? FVector2D(1.5) : FVector2D(1));
	
	SetVisibility(Target->IsPlayer() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}

bool UStructureSelector::TryInit(AStructure* InTarget)
{
	if(Target != nullptr)
	{
		return false;
	}

	Target = InTarget;

	// Manually sync indications as existing indications are not broadcast to new selector
	for(UStructureIndication* Indication : Target->GetIndications())
	{
		Indicators->AddIndicator(Indication);
	}

	Target->OnIndicationAdded.AddUObject<UStructureSelector>(this, &UStructureSelector::OnIndicationAdded);
	Target->OnIndicationRemoved.AddUObject<UStructureSelector>(this, &UStructureSelector::OnIndicationRemoved);

	return true;
}

AStructure* UStructureSelector::GetTarget() const
{
	return Target;
}

void UStructureSelector::HandleClick() const
{
	AStructure* Player = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(IsValid(Target) && IsValid(Player))
	{
		Player->SetTarget(Target);
	}
}

void UStructureSelector::OnIndicationAdded(UStructureIndication* Indication) const
{
	Indicators->AddIndicator(Indication);
}

void UStructureSelector::OnIndicationRemoved(UStructureIndication* Indication) const
{
	Indicators->RemoveIndicator(Indication);
}
