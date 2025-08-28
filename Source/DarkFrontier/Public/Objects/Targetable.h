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

	virtual bool IsTargetable(AStructure* Structure) const = 0;

	virtual TSubclassOf<USelector> GetSelectorClass() const = 0;

};
