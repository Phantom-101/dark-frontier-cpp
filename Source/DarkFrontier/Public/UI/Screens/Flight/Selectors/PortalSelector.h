// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Selector.h"
#include "PortalSelector.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UPortalSelector : public USelector
{
	GENERATED_BODY()

public:

	virtual void Update(const FGeometry& CanvasGeometry) override;
	
};
