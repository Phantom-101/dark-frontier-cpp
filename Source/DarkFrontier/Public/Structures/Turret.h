// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool CanActivate();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void TryActivate();

protected:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void OnActivate();

};
