// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureDamage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureDamage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	float Kinetic = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	float Explosive = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	float Beam = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	
	float Field = 0;

	FStructureDamage();

	FStructureDamage(float InKinetic, float InExplosive, float InBeam, float InField);

	float Sum() const;

	FStructureDamage Scale(float InFactor) const;

	void SetMagnitudes(TSubclassOf<class UStructureDamageTags> Tags, const struct FGameplayEffectSpecHandle& SpecHandle) const;
	
};
