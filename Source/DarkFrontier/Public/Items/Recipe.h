// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Recipe.generated.h"

class UItemList;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API URecipe : public UDataAsset
{
	GENERATED_BODY()

public:

	URecipe();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Time = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Cost = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TObjectPtr<UItemList> Inputs;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Revenue = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	TObjectPtr<UItemList> Outputs;
	
};
