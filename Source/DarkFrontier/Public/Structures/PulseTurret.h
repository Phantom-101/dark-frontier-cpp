// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "PulseTurret.generated.h"

class UNiagaraSystem;
class UStructureDamageType;
class UPulseAbility;
class UPulseTurretControl;

UCLASS()
class DARKFRONTIER_API APulseTurret : public ATurret
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	float EnergyCost = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	float DamageAmount = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UStructureDamageType> DamageType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	float Delay = 3;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<UNiagaraSystem> BeamSystem;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	TObjectPtr<AStructure> SavedTarget;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FTimerHandle DelayHandle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UPulseTurretControl> ControlClass;

public:

	APulseTurret();

	virtual bool CanActivate() override;

	virtual void OnActivate() override;

	virtual UStructurePartControl* CreateControl(UWidget* WidgetOwner) override;

protected:

	void OnDelayComplete();

};
