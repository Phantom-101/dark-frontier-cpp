// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogMailTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UniverseGameState.h"
#include "UI/Screens/LogUI/Mail.h"
#include "UI/Screens/LogUI/MailEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogMailTab::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UObject*> Mail;
	// TODO get mail from somewhere
	UMail* Temp = NewObject<UMail>();
	Temp->Subject = FText::FromString("Test subject");
	Temp->Body = FText::FromString("Test body");
	Temp->Timestamp = GetWorld()->GetGameState<AUniverseGameState>()->GetGameTimestamp();
	Temp->IsRead = false;
	Mail.Add(Temp);
	MailListBox->SetOptions(Mail);
	MailListBox->SetBuilder([Owner = this, Class = EntryClass](UObject* Faction)
	{
		UMailEntry* Option = CreateWidget<UMailEntry>(Owner, Class);
		Option->Init(Cast<UMail>(Faction));
		return Option;
	});

	MailListBox->OnChanged.AddUObject<ULogMailTab>(this, &ULogMailTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogMailTab>(this, &ULogMailTab::HandleBack);
}

void ULogMailTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		Switcher->SetActiveWidgetIndex(0);
	}
	else
	{
		Switcher->SetActiveWidgetIndex(1);
		SubjectText->SetText(FText::FromString(FString::Printf(TEXT("\"%s\""), *Cast<UMail>(Object)->Subject.ToString())));
		BodyText->SetText(Cast<UMail>(Object)->Body);
	}
}

void ULogMailTab::HandleBack() const
{
	MailListBox->SetCurrentOption(nullptr);
}
