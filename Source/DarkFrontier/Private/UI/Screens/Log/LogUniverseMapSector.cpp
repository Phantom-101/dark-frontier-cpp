// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogUniverseMapSector.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Sectors/Sector.h"
#include "UI/Screens/Log/LogUniverseMapConnection.h"
#include "UI/Screens/Log/LogUniverseMapTab.h"

void ULogUniverseMapSector::NativeConstruct()
{
	Super::NativeConstruct();
	SelectButton->OnClicked().AddUObject(this, &ULogUniverseMapSector::HandleSelect);
}

void ULogUniverseMapSector::Init(ULogUniverseMapTab* InTab, ASector* InSector)
{
	Tab = InTab;
	Sector = InSector;
	GUARD(IsValid(Tab) && IsValid(Sector));
	
	NameText->SetText(FText::FromString(Sector->GetActorNameOrLabel()));
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	PanelSlot->SetPosition(Sector->GetPosition());

	SectorImage->SetColorAndOpacity(Sector->GetColor());

	for(ASector* To : Sector->GetConnections())
	{
		ULogUniverseMapConnection* Connection = CreateWidget<ULogUniverseMapConnection>(this, ConnectionClass);
		Canvas->AddChild(Connection);
		Connection->Init(Sector, To);
		Connections.Add(To, Connection);
	}
}

void ULogUniverseMapSector::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Tab) && IsValid(Sector));
	SelectionImage->SetVisibility(Tab->GetSelected() == Sector ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void ULogUniverseMapSector::HandleSelect() const
{
	Tab->SetSelected(Sector);
}
