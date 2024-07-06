// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretAbility.h"
#include "PulseAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UPulseAbility : public UTurretAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag CueTag;

protected:

	virtual void OnActivate(UTurretPayload* Payload) override;
	
};
