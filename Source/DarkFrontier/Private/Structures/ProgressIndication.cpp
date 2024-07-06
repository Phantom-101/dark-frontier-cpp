// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/ProgressIndication.h"
#include "Blueprint/UserWidget.h"
#include "UI/Screens/GameUI/ProgressIndicator.h"

UStructureIndicator* UProgressIndication::CreateIndicator(UWidget* Owner)
{
	UProgressIndicator* Indicator = CreateWidget<UProgressIndicator>(Owner, IndicatorClass);
	Indicator->Indication = this;
	return Indicator;
}
