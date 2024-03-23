// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructurePartSlotFilter.h"
#include "StructurePartSlotTypeFilter.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartSlotTypeFilter : public UStructurePartSlotFilter
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TObjectPtr<class UStructurePartSlotType>> CompatibleTypes;

public:

	virtual bool IsCompatible(const UStructurePartSlot* Other) override;
	
};
