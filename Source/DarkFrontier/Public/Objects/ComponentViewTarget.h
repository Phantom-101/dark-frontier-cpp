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
class DARKFRONTIER_API UComponentViewTarget : public UObject, public IViewTarget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> Component;

	virtual FVector GetViewLocation() override;

	virtual FRotator GetViewRotation() override;

	virtual double GetViewDistance() override;
	
};
