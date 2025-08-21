// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/StatusBar.h"
#include "CommonButtonBase.h"
#include "Libraries/UIFunctionLibrary.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Screens.h"
#include "UI/Screens/Log/LogScreen.h"
#include "UI/Screens/Menu/MenuScreen.h"

void UStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

	LogButton->OnClicked().AddUObject<UStatusBar>(this, &UStatusBar::HandleLog);
	MenuButton->OnClicked().AddUObject<UStatusBar>(this, &UStatusBar::HandleMenu);
}

void UStatusBar::HandleLog() const
{
	UCommonActivatableWidgetContainerBase* Container = UUIFunctionLibrary::GetParentWidgetOfClass<UGameScreens>(this)->GetGameStack();
	if(UUIFunctionLibrary::IsWidgetOfType(Container, LogScreenClass.Get()))
	{
		UUIFunctionLibrary::PopWidget(Container);
	}
	else
	{
		UUIFunctionLibrary::FloatWidget(Container, LogScreenClass.Get());
	}
}

void UStatusBar::HandleMenu() const
{
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);
	// Should not matter as the menu button is inaccessible from the menu UI itself
	UUIFunctionLibrary::FloatWidget(Screens->GetStack(), MenuScreenClass.Get());
}
