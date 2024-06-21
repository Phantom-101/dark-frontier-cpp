// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureSlotFilter.h"
#include "StructureSlotTypeFilter.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotTypeFilter : public UStructureSlotFilter
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TObjectPtr<class UStructureSlotType>> CompatibleTypes;

public:

	virtual bool IsCompatible(const UStructureSlot* Other) override;
	
};
