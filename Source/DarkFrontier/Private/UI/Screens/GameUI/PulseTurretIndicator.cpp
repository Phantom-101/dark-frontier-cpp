// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/PulseTurretIndicator.h"
#include "CommonButtonBase.h"
#include "Structures/PulseTurret.h"

void UPulseTurretIndicator::NativeConstruct()
{
	Super::NativeConstruct();

	ActivateButton->OnClicked().Clear();
	ActivateButton->OnClicked().AddUObject<UPulseTurretIndicator>(this, &UPulseTurretIndicator::OnClicked);
}

void UPulseTurretIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ActivateButton->SetIsEnabled(IsValid(Turret) && Turret->CanActivate());
}

AStructurePart* UPulseTurretIndicator::GetPart()
{
	return Turret;
}

void UPulseTurretIndicator::OnClicked()
{
	if(IsValid(Turret))
	{
		Turret->TryActivate();
	}
}
