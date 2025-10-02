// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

class USectorLocation;
class UTargetable;
class AItemPod;
class AAsteroid;
class AStructure;

UCLASS()
class DARKFRONTIER_API ASector : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<USectorLocation>> Locations;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AStructure>> Structures;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AAsteroid>> Asteroids;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AItemPod>> ItemPods;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<UTargetable>> Targets;

public:

	const TSet<TObjectPtr<UTargetable>>& GetTargets() const;

	UFUNCTION(BlueprintCallable)
	void Register(USectorLocation* Location);

	UFUNCTION(BlueprintCallable)
	void Unregister(USectorLocation* Location);

};
