// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureAbilityProxy.h"
#include "StructureTurretAbilityProxy.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureTurretAbilityProxy : public UStructureAbilityProxy
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructureTurret> Turret;

	virtual void TryActivate() override;

	virtual float GetArcLength() override;

};
