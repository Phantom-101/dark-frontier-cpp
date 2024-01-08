// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartAction.generated.h"

DECLARE_DELEGATE(FStructurePartActionTriggered)

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UStructurePartAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText ActionName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<class UTexture2D> ActionIcon;

	FStructurePartActionTriggered OnTriggered;
	
	void Trigger() const;
	
};
