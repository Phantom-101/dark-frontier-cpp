// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/PulseTurretControl.h"
#include "CommonButtonBase.h"
#include "Structures/PulseTurret.h"

void UPulseTurretControl::NativeConstruct()
{
	Super::NativeConstruct();

	ActivateButton->OnClicked().Clear();
	ActivateButton->OnClicked().AddUObject<UPulseTurretControl>(this, &UPulseTurretControl::OnClicked);
}

void UPulseTurretControl::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ActivateButton->SetIsEnabled(IsValid(Turret) && Turret->CanActivate());
}

AStructurePart* UPulseTurretControl::GetPart()
{
	return Turret;
}

void UPulseTurretControl::OnClicked()
{
	if(IsValid(Turret))
	{
		Turret->TryActivate();
	}
}
