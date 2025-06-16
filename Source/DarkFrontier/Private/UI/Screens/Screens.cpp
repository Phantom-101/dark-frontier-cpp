// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Screens.h"
#include "CommonActivatableWidget.h"

UCommonActivatableWidgetStack* UScreens::GetStack() const
{
	return Stack;
}

TOptional<FUIInputConfig> UScreens::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}
