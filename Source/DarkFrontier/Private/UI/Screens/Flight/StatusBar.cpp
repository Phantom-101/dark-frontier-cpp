// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/StatusBar.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
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
	UCommonActivatableWidgetContainerBase* Container = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UGameScreens>(this)->GetGameStack();
	if(UUIBlueprintFunctionLibrary::IsWidgetOfType(Container, LogScreenClass.Get()))
	{
		UUIBlueprintFunctionLibrary::PopWidget(Container);
	}
	else
	{
		UUIBlueprintFunctionLibrary::FloatWidget(Container, LogScreenClass.Get());
	}
}

void UStatusBar::HandleMenu() const
{
	const UScreens* Screens = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);
	// Should not matter as the menu button is inaccessible from the menu UI itself
	UUIBlueprintFunctionLibrary::FloatWidget(Screens->GetStack(), MenuScreenClass.Get());
}
