// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

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
	TSet<TObjectPtr<AActor>> Actors;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AStructure>> Structures;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AAsteroid>> Asteroids;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AItemPod>> ItemPods;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UTargetable>> Targets;

public:

	const TArray<TObjectPtr<UTargetable>>& GetTargets();

	UFUNCTION(BlueprintCallable)
	void Register(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void Unregister(AActor* Actor);

	template<typename T>
	void TryRegister(AActor* Actor, TSet<TObjectPtr<T>>& Registry)
	{
		if(Actor->IsA<T>())
		{
			Registry.Add(Cast<T>(Actor));
		}
	}

	template<typename T>
	void TryUnregister(AActor* Actor, TSet<TObjectPtr<T>>& Registry)
	{
		if(Actor->IsA<T>())
		{
			Registry.Remove(Cast<T>(Actor));
		}
	}

};
