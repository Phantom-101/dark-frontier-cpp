// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

class ASector;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AFaction : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFaction();

protected:

	UPROPERTY(EditAnywhere)
	FText FactionName;

	// From -1 to 1, where -1 is resource extraction and production, 0 is manufacturing, and 1 is service industry
	UPROPERTY(EditAnywhere)
	float EconomicFocus = 0;

	// From -1 to 1, where -1 is horizontal integration, and 1 is vertical integration
	UPROPERTY(EditAnywhere)
	float EconomicIntegration = 0;

	// From -1 to 1, where -1 is unwilling to enter new markets, and 1 is willing to enter new markets
	UPROPERTY(EditAnywhere)
	float EconomicDiversity = 0;

	// From -1 to 1, where -1 is unwilling to expand to new locations, and 1 is willing to expand to new locations
	UPROPERTY(EditAnywhere)
	float EconomicExpansion = 0;

	// From -1 to 1, where -1 is piracy, 0 is peacekeeping, 1 is empire building
	UPROPERTY(EditAnywhere)
	float MilitaryFocus = 0;

	// From -1 to 1, where -1 is unwilling to build military logistics, and 1 is willing to build military logistics
	UPROPERTY(EditAnywhere)
	float MilitaryIntegration = 0;

	// From -1 to 1, where -1 is unwilling to maintain a diverse composition, and 1 is willing to maintain a diverse composition
	UPROPERTY(EditAnywhere)
	float MilitaryDiversity = 0;
	
	// From -1 to 1, where -1 is unwilling to expand to new locations, and 1 is willing to expand to new locations
	UPROPERTY(EditAnywhere)
	float MilitaryExpansion = 0;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ASector> Home;

	UPROPERTY(EditAnywhere)
	float Balance = 0;

	UPROPERTY(EditAnywhere)
	TMap<TObjectPtr<AFaction>, float> Relations;
	
	virtual void BeginPlay() override;

public:

	FText GetFactionName() const;

	ASector* GetHome() const;

	float GetBalance() const;

	void SetBalance(float Target);

	float ChangeBalance(float Delta);

	float GetRelation(AFaction* Other) const;

	void SetRelation(AFaction* Other, float Target);

	float ChangeRelation(AFaction* Other, float Delta);

	float GetPower() const;

	float GetReputation();
	
};
