// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/MailEntry.h"
#include "CommonTextBlock.h"
#include "Game/GameTimestamp.h"
#include "UI/Screens/LogUI/Mail.h"

void UMailEntry::Init(UMail* InMail)
{
	Mail = InMail;

	SubjectText->SetText(FText::FromString(FString::Printf(TEXT("\"%s\""), *Mail->Subject.ToString())));
	// TODO change to time ago
	TimeText->SetText(FText::FromString(FString::FromInt(Mail->Timestamp->Value)));
}
