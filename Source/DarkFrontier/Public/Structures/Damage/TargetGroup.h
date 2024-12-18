// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TargetGroup.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTargetGroup : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText GroupName;
	
};
