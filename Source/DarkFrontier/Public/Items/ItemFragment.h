// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.generated.h"

class AStructurePart;

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FItemFragment
{
	GENERATED_BODY()

	virtual ~FItemFragment() = default;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FItemColor : public FItemFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FLinearColor Color;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FAmmo : public FItemFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float ReloadTime;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AStructurePart>> CompatibleParts;
};
