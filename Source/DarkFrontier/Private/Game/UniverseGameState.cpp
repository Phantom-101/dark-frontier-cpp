// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/UniverseGameState.h"
#include "Game/GameTime.h"
#include "Game/GameTimestamp.h"

AUniverseGameState::AUniverseGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	Timestamp = CreateDefaultSubobject<UGameTimestamp>("Timestamp");
}

UGameTimestamp* AUniverseGameState::GetGameTimestamp() const
{
	return Timestamp;
}

UGameTime* AUniverseGameState::GetGameTime() const
{
	return UGameTime::FromTimestamp(Timestamp);
}

void AUniverseGameState::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Timestamp->Value += DeltaSeconds;
}
