// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructureShield.generated.h"

class UStructureShieldGameplay;

UCLASS()
class DARKFRONTIER_API AStructureShield : public AActor
{
	GENERATED_BODY()

public:

	AStructureShield();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureShieldGameplay> Gameplay;

public:

	UStructureShieldGameplay* GetGameplay();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
