// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "StructurePartFilter.generated.h"

class AStructurePart;

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter
{
	GENERATED_BODY()

	virtual ~FStructurePartFilter() = default;

	virtual bool Matches(const AStructurePart* Other) const;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter_MatchesAll : public FStructurePartFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(BaseStruct="StructurePartFilter"))
	TArray<TInstancedStruct<FStructurePartFilter>> Filters;

	virtual bool Matches(const AStructurePart* Other) const override;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter_MatchesAny : public FStructurePartFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(BaseStruct="StructurePartFilter"))
	TArray<TInstancedStruct<FStructurePartFilter>> Filters;

	virtual bool Matches(const AStructurePart* Other) const override;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter_HasAll : public FStructurePartFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer AllTags;

	virtual bool Matches(const AStructurePart* Other) const override;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter_HasAny : public FStructurePartFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer AnyTags;

	virtual bool Matches(const AStructurePart* Other) const override;
};

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructurePartFilter_HasNone : public FStructurePartFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer NoneTags;

	virtual bool Matches(const AStructurePart* Other) const override;
};
