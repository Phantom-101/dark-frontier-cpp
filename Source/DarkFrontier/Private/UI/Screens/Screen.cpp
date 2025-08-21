// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Screen.h"
#include "Input/CommonBoundActionButton.h"
#include "Input/CommonUIInputTypes.h"
#include "Libraries/UIFunctionLibrary.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Screens.h"

void UScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	UWidget* FocusTarget = GetDesiredFocusTarget();
	if(IsValid(FocusTarget))
	{
		FocusTarget->SetFocus();
	}
	RegisterBindings();
}

void UScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	UnregisterBindings();
}

FUIActionBindingHandle UScreen::Bind(const UInputAction* InputAction, const FSimpleDelegate& OnExecuteAction)
{
	return BindByArgs(FBindUIActionArgs(InputAction, OnExecuteAction));
}

FUIActionBindingHandle UScreen::BindScreen(const UInputAction* InputAction, const TSubclassOf<UCommonActivatableWidget>& ScreenClass)
{
	return BindFunction<UScreen>(InputAction, &UScreen::FloatScreen, ScreenClass, true);
}

FUIActionBindingHandle UScreen::BindByArgs(const FBindUIActionArgs& Args)
{
	const FUIActionBindingHandle Handle = RegisterUIActionBinding(Args);
	BindingHandles.Add(Handle);
	return Handle;
}

void UScreen::RegisterBindings()
{
}

void UScreen::UnregisterBindings()
{
	for(FUIActionBindingHandle Binding : BindingHandles)
	{
		Binding.Unregister();
	}
}

void UScreen::FloatScreen(const TSubclassOf<UCommonActivatableWidget> ScreenClass, const bool IsGame)
{
	if(IsGame)
	{
		const UGameScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UGameScreens>(this);
		UUIFunctionLibrary::FloatWidget(Screens->GetGameStack(), ScreenClass);
	}
	else
	{
		const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);
		UUIFunctionLibrary::FloatWidget(Screens->GetStack(), ScreenClass);
	}
}
