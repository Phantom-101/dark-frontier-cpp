// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/Mail.h"
#include "Factions/Faction.h"
#include "Game/UniverseGameState.h"

UMail* UMail::NewMail(AFaction* InSender, const FText& InSubject, const FText& InBody)
{
	UMail* Mail = NewObject<UMail>();
	Mail->Subject = InSubject;
	Mail->Body = InBody;
	Mail->Sender = InSender;
	Mail->Timestamp = InSender->GetWorld()->GetGameState<AUniverseGameState>()->GetTimestamp();
	return Mail;
}
