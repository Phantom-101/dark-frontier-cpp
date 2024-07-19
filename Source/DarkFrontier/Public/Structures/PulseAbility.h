// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretAbility.h"
#include "PulseAbility.generated.h"

class UHitscanIndication;
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
	TSubclassOf<UHitscanIndication> IndicationClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag CueTag;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UTurretPayload> CurrentPayload;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UHitscanTask> CurrentTask;

	virtual void OnActivate(UTurretPayload* Payload) override;

private:

	UFUNCTION()
	void OnDelayFinish();
	
};
