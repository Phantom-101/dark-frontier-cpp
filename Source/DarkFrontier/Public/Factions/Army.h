// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Army.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UArmy : public UObject
{
	GENERATED_BODY()

public:

	UArmy();
	
	explicit UArmy(int StartingCount, class AFaction* Faction);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Attack = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Defense = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Health = 1;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<UArmy>, double> Effectiveness = {};

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	double BuffMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	int32 Count = 1;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AFaction> OwningFaction;

	UFUNCTION(BlueprintCallable)
	UArmy* GetPreferredTarget(TArray<UArmy*> Armies);

	UFUNCTION(BlueprintCallable)
	void AttackTarget(UArmy* Target);

private:

	UFUNCTION()
	double GetAttackPreference(UArmy* Army);

	UFUNCTION()
	double GetEffectiveness(const UArmy* Army);
	
};
