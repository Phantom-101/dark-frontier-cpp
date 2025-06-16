// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Controls/PulseTurretControls.h"
#include "CommonButtonBase.h"
#include "Structures/PulseTurret.h"

void UPulseTurretControls::NativeConstruct()
{
	Super::NativeConstruct();

	ActivateButton->OnClicked().Clear();
	ActivateButton->OnClicked().AddUObject<UPulseTurretControls>(this, &UPulseTurretControls::OnClicked);
}

void UPulseTurretControls::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APulseTurret* Turret = Cast<APulseTurret>(Part);
	ActivateButton->SetIsEnabled(IsValid(Turret) && Turret->CanActivate());
}

bool UPulseTurretControls::TryInitialize(AStructurePart* InPart)
{
	if(Cast<APulseTurret>(InPart) == nullptr)
	{
		return false;
	}

	return Super::TryInitialize(InPart);
}

void UPulseTurretControls::OnClicked()
{
	APulseTurret* Turret = Cast<APulseTurret>(Part);
	if(IsValid(Turret))
	{
		Turret->TryActivate();
	}
}
