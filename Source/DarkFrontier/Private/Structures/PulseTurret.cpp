// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseTurret.h"
#include "Blueprint/UserWidget.h"
#include "Structures/PulseAbility.h"
#include "UI/Screens/GameUI/PulseTurretIndicator.h"

APulseTurret::APulseTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

TSubclassOf<UTurretAbility> APulseTurret::GetAbilityClass()
{
	return AbilityClass;
}

UStructurePartIndicator* APulseTurret::CreateIndicator(UWidget* WidgetOwner)
{
	UPulseTurretIndicator* Indicator = CreateWidget<UPulseTurretIndicator>(WidgetOwner, IndicatorClass);
	Indicator->Turret = this;
	return Indicator;
}
