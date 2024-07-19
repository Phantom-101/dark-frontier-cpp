// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

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

public:

	UFUNCTION(BlueprintCallable)
	void RegisterStructure(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	void UnregisterStructure(AStructure* Structure);

};
