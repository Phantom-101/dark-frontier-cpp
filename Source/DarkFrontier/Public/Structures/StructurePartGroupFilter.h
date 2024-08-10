// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartFilter.h"
#include "StructurePartGroupFilter.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartGroupFilter : public UStructurePartFilter
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TObjectPtr<class UStructurePartGroup>> CompatibleGroups;

public:

	virtual bool IsCompatible(const AStructurePart* Other) override;
	
};
