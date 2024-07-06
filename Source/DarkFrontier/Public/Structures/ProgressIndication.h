// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/StructureIndication.h"
#include "ProgressIndication.generated.h"

class UProgressIndicator;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UProgressIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UProgressIndicator> IndicatorClass;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float Progress = 0;

	virtual UStructureIndicator* CreateIndicator(UWidget* Owner) override;

};
