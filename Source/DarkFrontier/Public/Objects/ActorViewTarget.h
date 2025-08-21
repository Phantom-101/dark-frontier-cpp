// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewTarget.h"
#include "ActorViewTarget.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UActorViewTarget : public UViewTarget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AActor> Actor;

	static UActorViewTarget* New(AActor* Actor);

	virtual bool IsValid() override;

	virtual FVector GetViewLocation() override;

	virtual FRotator GetViewRotation() override;

	virtual double GetViewDistance() override;

};
