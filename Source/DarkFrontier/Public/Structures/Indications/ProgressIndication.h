// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureIndication.h"
#include "ProgressIndication.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UProgressIndication : public UStructureIndication
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float Progress = 0;
	
};
