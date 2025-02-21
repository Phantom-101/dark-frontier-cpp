// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/UniverseGameState.h"
#include "Game/Time.h"
#include "Game/Timestamp.h"

AUniverseGameState::AUniverseGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

FTimestamp AUniverseGameState::GetTimestamp() const
{
	return Timestamp;
}

FTime AUniverseGameState::GetTime() const
{
	return FTime(Timestamp);
}

AFaction* AUniverseGameState::GetPlayerFaction()
{
	return PlayerFaction;
}

void AUniverseGameState::SetPlayerFaction(AFaction* Faction)
{
	if(Faction != nullptr)
	{
		PlayerFaction = Faction;
	}
}

TArray<UMail*> AUniverseGameState::GetMail()
{
	return Mail;
}

void AUniverseGameState::AddMail(UMail* InMail)
{
	Mail.Add(InMail);
}

void AUniverseGameState::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Timestamp.Value += DeltaSeconds;
}
