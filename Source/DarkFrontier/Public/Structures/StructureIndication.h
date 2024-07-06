// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.generated.h"

class UStructureIndicator;
class UWidget;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class DARKFRONTIER_API UStructureIndication : public UObject
{
	GENERATED_BODY()

public:

	virtual UStructureIndicator* CreateIndicator(UWidget* Owner);
	
};
