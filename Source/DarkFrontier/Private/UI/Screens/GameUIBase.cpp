// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUIBase.h"

UCommonActivatableWidgetStack* UGameUIBase::GetGameStack() const
{
	return GameStack;
}

TOptional<FUIInputConfig> UGameUIBase::GetDesiredInputConfig() const
{
	return TOptional<FUIInputConfig>();
}
