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
	FGameplayTag PayloadTag;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void Activate(class UTurretPayload* Payload);
	
private:

	UFUNCTION()
	void HandlePayloadReceived(FGameplayEventData Payload);
	
};
