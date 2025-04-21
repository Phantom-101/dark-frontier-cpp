// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureDamageType.h"
#include "CompositeDamageType.generated.h"

USTRUCT(BlueprintType)
struct DARKFRONTIER_API FCompositeDamageEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UStructureDamageType> DamageType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Weight;

	FCompositeDamageEntry();

	FCompositeDamageEntry(const TSubclassOf<UStructureDamageType>& InDamageType, float InWeight);

	bool IsValid() const;
	
};

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCompositeDamageType : public UStructureDamageType
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FCompositeDamageEntry> Entries;

public:
	
	virtual float Evaluate(const UTargetGroup* TargetGroup) const override;

};
