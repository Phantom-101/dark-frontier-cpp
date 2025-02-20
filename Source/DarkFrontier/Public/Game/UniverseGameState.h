// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "UniverseGameState.generated.h"

class UGameTime;
class UGameTimestamp;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AUniverseGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UGameTimestamp> Timestamp;

public:

	AUniverseGameState();

	UFUNCTION(BlueprintCallable)
	UGameTimestamp* GetGameTimestamp() const;

	UFUNCTION(BlueprintCallable)
	UGameTime* GetGameTime() const;

	virtual void Tick(float DeltaSeconds) override;

};
