// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

class AItemPod;
class AAsteroid;
class ITargetable;
class AStructure;

UCLASS()
class DARKFRONTIER_API ASector : public AActor
{
	GENERATED_BODY()

public:

	ASector();

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
	TArray<TScriptInterface<ITargetable>> Targets;

public:

	const TArray<TScriptInterface<ITargetable>>& GetTargets();

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
