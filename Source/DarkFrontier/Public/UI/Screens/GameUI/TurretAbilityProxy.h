// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureAbilityProxy.h"
#include "TurretAbilityProxy.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTurretAbilityProxy : public UStructureAbilityProxy
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class ATurret> Turret;

	virtual void TryActivate() override;

	virtual float GetArcLength() override;

};
