// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UCombatant : public UObject
{
	GENERATED_BODY()

public:

	UCombatant();
	
	explicit UCombatant(int StartingCount, class AFaction* Faction);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Attack = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Defense = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	double Health = 1;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<UCombatant>, double> Effectiveness = {};

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	double BuffMultiplier = 1;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	int32 Count = 1;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AFaction> OwningFaction;

	UFUNCTION(BlueprintCallable)
	UCombatant* GetPreferredTarget(TArray<UCombatant*> Combatants);

	UFUNCTION(BlueprintCallable)
	void AttackTarget(UCombatant* Target);

private:

	UFUNCTION()
	double GetAttackPreference(UCombatant* Combatant);

	UFUNCTION()
	double GetEffectiveness(const UCombatant* Combatant);
	
};
