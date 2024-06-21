// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretPayload.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTurretPayload : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class AStructure> Instigator;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class ATurret> Turret;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USceneComponent> SourceTransform;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AStructure> Target;
	
};
