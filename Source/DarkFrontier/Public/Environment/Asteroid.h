// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Targetable.h"
#include "Asteroid.generated.h"

class USectorLocation;
class UAsteroidSelector;
class AItemPod;
class ASector;
class UItem;

UCLASS()
class DARKFRONTIER_API AAsteroid : public AActor, public ISectorLocationInterface, public ITargetableInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<TObjectPtr<UItem>, float> Composition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int MaxAmount = 1000;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int DepletedAmount = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float AmountPerDamage = 0.01;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AItemPod> PodClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USectorLocation> Location;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTargetable> Targetable;

public:

	AAsteroid();

	const TMap<TObjectPtr<UItem>, float>& GetComposition() const;

	float GetMaxWeight() const;

	int GetMaxAmount() const;

	int GetDepletedAmount() const;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	COMPONENT_ACCESSOR_NAME(SectorLocation, Location);
	COMPONENT_ACCESSOR(Targetable);

protected:

	void CreatePod();

	UItem* RandomItem() const;

};
