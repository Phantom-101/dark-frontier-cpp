// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Time.h"
#include "Timestamp.h"
#include "GameFramework/GameState.h"
#include "UniverseGameState.generated.h"

class UMail;
class AFaction;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AUniverseGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FTimestamp Timestamp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AFaction> PlayerFaction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TObjectPtr<UMail>> Mail;

public:

	AUniverseGameState();

	UFUNCTION(BlueprintCallable)
	FTimestamp GetTimestamp() const;

	UFUNCTION(BlueprintCallable)
	FTime GetTime() const;

	UFUNCTION(BlueprintCallable)
	AFaction* GetPlayerFaction();

	UFUNCTION(BlueprintCallable)
	void SetPlayerFaction(AFaction* Faction);

	UFUNCTION(BlueprintCallable)
	TArray<UMail*> GetMail();

	UFUNCTION(BlueprintCallable)
	void AddMail(UMail* InMail);

protected:

	virtual void Tick(float DeltaSeconds) override;

};
