// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameScreens.h"

UCommonActivatableWidgetStack* UGameScreens::GetGameStack() const
{
	return GameStack;
}

TOptional<FUIInputConfig> UGameScreens::GetDesiredInputConfig() const
{
	return TOptional<FUIInputConfig>();
}
