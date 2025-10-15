// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Overview/InfoOverviewTab.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "UI/Screens/Info/InfoScreen.h"
#include "UI/Screens/Info/Overview/StructureOverview.h"

void UInfoOverviewTab::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Screen));

	AActor* Actor = Screen->GetActor();
	GUARD(IsValid(Actor));

	NameText->SetText(FText::FromString(Actor->GetActorNameOrLabel()));
	if(Actor->IsA<AStructure>())
	{
		OverviewSwitcher->SetActiveWidget(StructureOverview);
		StructureOverview->Init(Cast<AStructure>(Actor));
	}
	else
	{
		OverviewSwitcher->SetActiveWidget(UnknownOverview);
	}
}
