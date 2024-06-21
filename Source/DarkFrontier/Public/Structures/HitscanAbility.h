// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretAbility.h"
#include "HitscanAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHitscanAbility : public UTurretAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

protected:

	virtual void Activate(UTurretPayload* Payload) override;

	virtual void OnHit(class UHitscanResult* Result);
	
};
