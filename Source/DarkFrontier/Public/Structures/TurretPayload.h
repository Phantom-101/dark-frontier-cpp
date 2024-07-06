// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretPayload.generated.h"

class AStructure;
class ATurret;
class UTurretSource;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTurretPayload : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AStructure> Instigator;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATurret> Turret;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UTurretSource> Source;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AStructure> Target;
	
};
