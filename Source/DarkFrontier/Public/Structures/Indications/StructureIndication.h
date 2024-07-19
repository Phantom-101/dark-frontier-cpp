// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.generated.h"

class UStructureIndicatorGroup;
class UStructureIndicator;
class AStructure;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class DARKFRONTIER_API UStructureIndication : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UStructureIndicatorGroup> IndicatorGroupClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UStructureIndicator> IndicatorClass;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> Structure;

public:

	bool TryInit(AStructure* InStructure);

	AStructure* GetStructure() const;
	
};
