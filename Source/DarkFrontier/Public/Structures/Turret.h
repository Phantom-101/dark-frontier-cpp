// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

class UTargetable;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual bool CanActivate(UTargetable* InTarget) const;

	UFUNCTION(BlueprintCallable)
	virtual void TryActivate(UTargetable* InTarget);

protected:

	UFUNCTION(BlueprintCallable)
	virtual void OnActivate(UTargetable* InTarget);

};
