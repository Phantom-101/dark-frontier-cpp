// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

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
	TArray<TObjectPtr<AStructure>> Structures;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TScriptInterface<ITargetable>> Targets;

public:

	const TArray<TScriptInterface<ITargetable>>& GetTargets();

	UFUNCTION(BlueprintCallable)
	void RegisterStructure(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	void UnregisterStructure(AStructure* Structure);

};
