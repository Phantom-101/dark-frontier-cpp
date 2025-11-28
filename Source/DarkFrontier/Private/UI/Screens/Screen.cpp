// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Screen.h"
#include "Input/CommonBoundActionButton.h"
#include "Input/CommonUIInputTypes.h"
#include "Libraries/UIFunctionLibrary.h"
#include "UI/Screens/GameScreens.h"
#include "UI/Screens/Screens.h"

void UScreen::NativeConstruct()
{
	Super::NativeConstruct();
	RegisterBindings();
}

void UScreen::NativeDestruct()
{
	Super::NativeDestruct();
	UnregisterBindings();
}

void UScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	UWidget* FocusTarget = GetDesiredFocusTarget();
	if(IsValid(FocusTarget))
	{
		FocusTarget->SetFocus();
	}
}

FUIActionBindingHandle UScreen::Bind(const UInputAction* InputAction, const FSimpleDelegate& OnExecuteAction)
{
	return BindByArgs(FBindUIActionArgs(InputAction, OnExecuteAction));
}

FUIActionBindingHandle UScreen::BindScreen(const UInputAction* InputAction, const TSubclassOf<UCommonActivatableWidget>& ScreenClass)
{
	return BindFunction<UScreen>(InputAction, &UScreen::FloatScreenDiscard, ScreenClass, true);
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

UCommonActivatableWidget* UScreen::FloatScreen(const TSubclassOf<UCommonActivatableWidget>& ScreenClass, const bool IsGame) const
{
	if(IsGame)
	{
		const UGameScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UGameScreens>(this);
		return UUIFunctionLibrary::FloatWidget(Screens->GetGameStack(), ScreenClass);
	}
	
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);
	return UUIFunctionLibrary::FloatWidget(Screens->GetStack(), ScreenClass);
}

void UScreen::FloatScreenDiscard(const TSubclassOf<UCommonActivatableWidget> ScreenClass, const bool IsGame)
{
	(void)FloatScreen(ScreenClass, IsGame);
}
