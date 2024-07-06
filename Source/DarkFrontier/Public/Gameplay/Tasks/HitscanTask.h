// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HitscanTask.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UHitscanTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FVector StartLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FVector EndLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_PhysicsBody;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TArray<TObjectPtr<AActor>> IgnoredActors;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FHitResult HitResult;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> HitPart;

	static UHitscanTask* New(UGameplayAbility* OwningAbility, const FVector& InStart, const FVector& InEnd, ECollisionChannel InChannel, const TArray<AActor*>& InIgnored);

	virtual void Activate() override;
	
};
