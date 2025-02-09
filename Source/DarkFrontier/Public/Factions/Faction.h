// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AFaction : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFaction();

	UPROPERTY(EditAnywhere)
	FText FactionName;

	// From -1 to 1, where -1 is resource extraction and production, 0 is manufacturing, and 1 is service industry
	UPROPERTY(EditAnywhere)
	double EconomicFocus;

	// From -1 to 1, where -1 is horizontal integration, and 1 is vertical integration
	UPROPERTY(EditAnywhere)
	double EconomicIntegration;

	// From -1 to 1, where -1 is unwilling to enter new markets, and 1 is willing to enter new markets
	UPROPERTY(EditAnywhere)
	double EconomicDiversity;

	// From -1 to 1, where -1 is unwilling to expand to new locations, and 1 is willing to expand to new locations
	UPROPERTY(EditAnywhere)
	double EconomicExpansion;

	// From -1 to 1, where -1 is piracy, 0 is peacekeeping, 1 is empire building
	UPROPERTY(EditAnywhere)
	double MilitaryFocus;

	// From -1 to 1, where -1 is unwilling to build military logistics, and 1 is willing to build military logistics
	UPROPERTY(EditAnywhere)
	double MilitaryIntegration;

	// From -1 to 1, where -1 is unwilling to maintain a diverse composition, and 1 is willing to maintain a diverse composition
	UPROPERTY(EditAnywhere)
	double MilitaryDiversity;
	
	// From -1 to 1, where -1 is unwilling to expand to new locations, and 1 is willing to expand to new locations
	UPROPERTY(EditAnywhere)
	double MilitaryExpansion;

	UPROPERTY(EditAnywhere)
	double Wealth = 0;

	UPROPERTY(EditAnywhere)
	TMap<TObjectPtr<AFaction>, double> Relations;

protected:
	
	virtual void BeginPlay() override;

public:

	double GetWealth() const;

	void SetWealth(double Target);

	double ChangeWealth(double Delta);

	double GetRelation(AFaction* Other) const;

	void SetRelation(AFaction* Other, double Target);

	double ChangeRelation(AFaction* Other, double Delta);
	
};
