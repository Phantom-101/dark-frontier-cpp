// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TickLevel.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Structure.h"

UTickLevel::UTickLevel()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 10;
}

void UTickLevel::BeginPlay()
{
	Super::BeginPlay();

	// Initial broadcast which may or may not be necessary
	OnTickLevelChanged.Broadcast(TickLevel);

	if(GetOwner()->Implements<USectorLocationInterface>())
	{
		SectorLocation = GetOwner<ISectorLocationInterface>()->GetSectorLocation();
		SectorLocation->OnSectorChanged.AddUObject(this, &UTickLevel::UpdateTickLevel);
		UpdateTickLevel(SectorLocation->GetSector());
	}
}

void UTickLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(IsValid(SectorLocation))
	{
		SectorLocation->OnSectorChanged.RemoveAll(this);
	}
}

void UTickLevel::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsValid(SectorLocation))
	{
		// Manually update at slow interval to handle when player instead of owner changes sectors
		UpdateTickLevel(SectorLocation->GetSector());
	}
}

ETickLevel UTickLevel::GetTickLevel() const
{
	return TickLevel;
}

void UTickLevel::UpdateTickLevel(ASector* Sector)
{
	const AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	GUARD(IsValid(Player));

	const ASector* PlayerSector = Player->GetSectorLocation()->GetSector();
	const ETickLevel NewTickLevel = Sector == PlayerSector ? ETickLevel::Full : ETickLevel::Partial;

	if(TickLevel != NewTickLevel)
	{
		TickLevel = NewTickLevel;
		OnTickLevelChanged.Broadcast(TickLevel);
	}
}
