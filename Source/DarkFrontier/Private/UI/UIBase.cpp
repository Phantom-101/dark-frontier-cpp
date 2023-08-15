// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UIBase.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidget* UUIBase::PeekGame() const
{
	return GameStack->GetActiveWidget();
}

UCommonActivatableWidget* UUIBase::PushGame(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Game stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
	return GameStack->AddWidget(WidgetClass);
}

UCommonActivatableWidget* UUIBase::PeekGameMenu() const
{
	return GameMenuStack->GetActiveWidget();
}

UCommonActivatableWidget* UUIBase::PushGameMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("GameMenu stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
	return GameMenuStack->AddWidget(WidgetClass);
}

UCommonActivatableWidget* UUIBase::PeekMenu() const
{
	return MenuStack->GetActiveWidget();
}

UCommonActivatableWidget* UUIBase::PushMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Menu stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
	return MenuStack->AddWidget(WidgetClass);
}

UCommonActivatableWidget* UUIBase::PeekModal() const
{
	return ModalStack->GetActiveWidget();
}

UCommonActivatableWidget* UUIBase::PushModal(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Modal stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
	return ModalStack->AddWidget(WidgetClass);
}
