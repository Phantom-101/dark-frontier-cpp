// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/MailEntry.h"
#include "CommonTextBlock.h"
#include "Game/Timestamp.h"
#include "Game/UniverseGameState.h"
#include "UI/Screens/LogUI/Mail.h"

void UMailEntry::Init(UMail* InMail)
{
	Mail = InMail;

	SubjectText->SetText(FText::FromString(FString::Printf(TEXT("\"%s\""), *Mail->Subject.ToString())));
	const FTimestamp Difference = Mail->Timestamp.Difference(GetWorld()->GetGameState<AUniverseGameState>()->GetTimestamp());
	TimeText->SetText(FText::FromString(FString::Printf(TEXT("%s ago"), *FTime(Difference).ToString())));
}
