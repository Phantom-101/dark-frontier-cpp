// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ViewTarget.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UViewTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFRONTIER_API IViewTarget
{
	GENERATED_BODY()

public:

	virtual FVector GetViewLocation();

	virtual FRotator GetViewRotation();

	virtual double GetViewDistance();

	static FBoxSphereBounds GetLocalBounds(const AActor* Actor, const bool OnlyCollidingComponents);
	
};
