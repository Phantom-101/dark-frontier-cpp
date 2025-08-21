// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

class ITargetable;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool CanActivate(const TScriptInterface<ITargetable>& Target);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void TryActivate(const TScriptInterface<ITargetable>& Target);

protected:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void OnActivate(const TScriptInterface<ITargetable>& Target);

};
