// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/UIBase.h"
#include "CommonActivatableWidget.h"

UCommonActivatableWidgetStack* UUIBase::GetStack() const
{
	return Stack;
}

TOptional<FUIInputConfig> UUIBase::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}
