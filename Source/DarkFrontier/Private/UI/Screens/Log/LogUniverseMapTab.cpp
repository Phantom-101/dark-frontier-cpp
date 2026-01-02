// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogUniverseMapTab.h"
#include "EngineUtils.h"
#include "Components/CanvasPanel.h"
#include "Sectors/Sector.h"
#include "UI/Screens/Log/LogUniverseMapSector.h"

void ULogUniverseMapTab::NativeConstruct()
{
	Super::NativeConstruct();
	SectorCanvas->ClearChildren();
	// TODO get from sector registry in game mode
	for(TActorIterator<ASector> It(GetWorld()); It; ++It)
	{
		ASector* Sector = *It;
		ULogUniverseMapSector* SectorWidget = CreateWidget<ULogUniverseMapSector>(this, SectorClass);
		SectorCanvas->AddChildToCanvas(SectorWidget);
		SectorWidget->Init(this, Sector);
	}
}

ASector* ULogUniverseMapTab::GetSelected() const
{
	return Selected;
}

void ULogUniverseMapTab::SetSelected(ASector* InSelected)
{
	Selected = InSelected;
}
