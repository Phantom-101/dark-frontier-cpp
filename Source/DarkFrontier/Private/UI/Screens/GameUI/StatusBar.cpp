// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StatusBar.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/GameUIBase.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/LogUI/LogUI.h"
#include "UI/Screens/MenuUI/MenuUI.h"

void UStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

	LogButton->OnClicked().AddUObject<UStatusBar>(this, &UStatusBar::HandleLog);
	MenuButton->OnClicked().AddUObject<UStatusBar>(this, &UStatusBar::HandleMenu);
}

void UStatusBar::HandleLog() const
{
	UCommonActivatableWidgetContainerBase* Container = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UGameUIBase>(this)->GetGameStack();
	if(UUIBlueprintFunctionLibrary::IsWidgetOfType(Container, LogUIClass))
	{
		UUIBlueprintFunctionLibrary::PopWidget(Container);
	}
	else
	{
		UUIBlueprintFunctionLibrary::FloatWidget(Container, LogUIClass);
	}
}

void UStatusBar::HandleMenu() const
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);
	// Should not matter as the menu button is inaccessible from the menu UI itself
	UUIBlueprintFunctionLibrary::FloatWidget(Base->GetStack(), MenuUIClass);
}
