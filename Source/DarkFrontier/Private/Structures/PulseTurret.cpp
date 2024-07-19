// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/PulseTurret.h"
#include "Blueprint/UserWidget.h"
#include "Structures/PulseAbility.h"
#include "UI/Screens/GameUI/PulseTurretControl.h"

APulseTurret::APulseTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

TSubclassOf<UTurretAbility> APulseTurret::GetAbilityClass()
{
	return AbilityClass;
}

UStructurePartControl* APulseTurret::CreateControl(UWidget* WidgetOwner)
{
	UPulseTurretControl* Control = CreateWidget<UPulseTurretControl>(WidgetOwner, ControlClass);
	Control->Turret = this;
	return Control;
}
