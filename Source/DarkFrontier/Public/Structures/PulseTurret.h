// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "PulseTurret.generated.h"

class UPulseAbility;
class UPulseTurretControl;

UCLASS()
class DARKFRONTIER_API APulseTurret : public ATurret
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UPulseAbility> AbilityClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UPulseTurretControl> ControlClass;

public:

	APulseTurret();

	virtual TSubclassOf<UTurretAbility> GetAbilityClass() override;

	virtual UStructurePartControl* CreateControl(UWidget* WidgetOwner) override;

};
