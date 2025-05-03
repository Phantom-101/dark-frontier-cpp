// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "StructureDamageType.generated.h"

class UTargetGroup;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureDamageType : public UDamageType
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TObjectPtr<UTargetGroup>, float> DamageMultiplierMap;

public:

	virtual float Evaluate(const UTargetGroup* TargetGroup) const;
	
};
