// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureAbility.h"
#include "TurretAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTurretAbility : public UStructureAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag PayloadEventTag;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	TObjectPtr<class UAbilityTask_WaitGameplayEvent> WaitEventTask;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag CueTag;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void HandleEventDataReceived(FGameplayEventData Payload);
	
};
