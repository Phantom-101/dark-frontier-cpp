// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogMailTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UniverseGameState.h"
#include "UI/Screens/Log/Mail.h"
#include "UI/Screens/Log/MailEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogMailTab::NativeConstruct()
{
	Super::NativeConstruct();

	MailListBox->SetOptions(TArray<UObject*>(GetWorld()->GetGameState<AUniverseGameState>()->GetMail()));
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
