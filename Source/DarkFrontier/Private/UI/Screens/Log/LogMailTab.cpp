// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogMailTab.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UniverseGameState.h"
#include "UI/Screens/Log/Mail.h"

void ULogMailTab::NativeConstruct()
{
	Super::NativeConstruct();

	ListView->OnItemSelectionChanged().AddUObject<ULogMailTab>(this, &ULogMailTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogMailTab>(this, &ULogMailTab::HandleBack);
}

void ULogMailTab::NativeOnActivated()
{
	Super::NativeOnActivated();

	const UObject* Selected = ListView->GetSelectedItem();
	
	ListView->SetListItems(GetWorld()->GetGameState<AUniverseGameState>()->GetMail());

	ListView->SetSelectedItem(Selected);
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
	ListView->ClearSelection();
}
