// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewTarget.h"
#include "UObject/Object.h"
#include "ComponentViewTarget.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UComponentViewTarget : public UViewTarget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> Component;

	static UComponentViewTarget* New(USceneComponent* Component);

	virtual bool IsValid() override;

	virtual FVector GetViewLocation() override;

	virtual FRotator GetViewRotation() override;

	virtual double GetViewDistance() override;
	
};
