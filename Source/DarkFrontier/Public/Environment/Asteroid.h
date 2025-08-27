// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Targetable.h"
#include "Asteroid.generated.h"

class AItemPod;
class ASector;
class UItem;

UCLASS()
class DARKFRONTIER_API AAsteroid : public AActor, public ITargetable
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
	TObjectPtr<ASector> Sector;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<USelector> SelectorClass;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	const TMap<TObjectPtr<UItem>, float>& GetComposition() const;

	float GetMaxWeight() const;

	int GetMaxAmount() const;

	int GetDepletedAmount() const;

	virtual FVector GetTargetLocation() override;

	virtual bool IsTargetable(AStructure* Structure) const override;

	virtual TSubclassOf<USelector> GetSelectorClass() const override;

	virtual bool ShouldShowSelector() const override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	void CreatePod();

	UItem* RandomItem() const;

};
