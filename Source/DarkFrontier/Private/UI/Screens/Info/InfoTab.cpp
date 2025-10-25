// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/InfoTab.h"
#include "UI/Widgets/Interaction/Tabs.h"

bool UInfoTab::IsRelevant(AActor* Actor) const
{
	return true;
}

const TObjectPtr<UTexture2D>& UInfoTab::GetTabIcon() const
{
	return TabIcon;
}

const FText& UInfoTab::GetTabName() const
{
	return TabName;
}

UTab* UInfoTab::NewTab(const TSubclassOf<UInfoTab>& TabClass)
{
	UTab* Tab = NewObject<UTab>();
	Tab->WidgetClass = TabClass;
	Tab->Icon = TabClass->GetDefaultObject<UInfoTab>()->TabIcon;
	Tab->Name = TabClass->GetDefaultObject<UInfoTab>()->TabName;
	return Tab;
}

void UInfoTab::Init(UInfoScreen* InScreen)
{
	Screen = InScreen;
}
