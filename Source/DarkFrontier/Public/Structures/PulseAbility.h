// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structures/HitscanAbility.h"
#include "PulseAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UPulseAbility : public UHitscanAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag CueTag;

protected:

	virtual void OnHit(UHitscanResult* Result) override;
	
};
