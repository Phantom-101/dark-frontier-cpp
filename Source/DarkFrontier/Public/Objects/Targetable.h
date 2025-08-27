// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Targetable.generated.h"

class AStructure;
class USelector;

UINTERFACE()
class UTargetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFRONTIER_API ITargetable
{
	GENERATED_BODY()

public:
	virtual FVector GetTargetLocation() = 0;

	virtual bool IsTargetable(AStructure* Structure) const = 0;

	virtual TSubclassOf<USelector> GetSelectorClass() const = 0;

	// TODO consider moving to selector widget class
	virtual bool ShouldShowSelector() const = 0;

	bool IsSelectedByPlayer() const;
};
