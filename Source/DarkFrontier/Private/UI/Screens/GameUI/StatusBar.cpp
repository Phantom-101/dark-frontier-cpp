// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StatusBar.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/LogUI/LogUI.h"

void UStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

	LogButton->OnClicked().AddUObject<UStatusBar>(this, &UStatusBar::HandleLog);
}

void UStatusBar::HandleLog() const
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);
	(void)Base->PushGameMenu<ULogUI>(LogUIClass);
}
