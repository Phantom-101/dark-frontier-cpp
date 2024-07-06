// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitscanResult.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHitscanResult : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTurretPayload> Payload;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class AStructurePart> HitPart;

	UPROPERTY(BlueprintReadWrite)
	FHitResult HitResult;
	
};
