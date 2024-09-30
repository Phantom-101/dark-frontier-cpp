// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretAbility.h"
#include "PulseAbility.generated.h"

class UStructureDamageType;
class UTimerIndication;
class UHitscanTask;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UPulseAbility : public UTurretAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	float Delay = 3;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UTimerIndication> IndicationClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag CueTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float DamageAmount = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UStructureDamageType> DamageType;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<const UTurretPayload> CurrentPayload;

	virtual void OnActivate(const UTurretPayload* Payload) override;

private:

	UFUNCTION()
	void OnDelayFinish();
	
};
