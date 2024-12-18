// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasTargetGroup.generated.h"

class UTargetGroup;

UINTERFACE()
class UHasTargetGroup : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFRONTIER_API IHasTargetGroup
{
	GENERATED_BODY()

public:

	virtual UTargetGroup* GetTargetGroup() const = 0;
	
};
