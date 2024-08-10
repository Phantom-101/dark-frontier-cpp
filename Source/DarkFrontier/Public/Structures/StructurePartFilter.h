// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartFilter.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UStructurePartFilter : public UObject
{
	GENERATED_BODY()

public:

	virtual bool IsCompatible(const AStructurePart* Other);
	
};
