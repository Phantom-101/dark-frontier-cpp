// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartActionGroup.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKFRONTIER_API UStructurePartActionGroup : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText GroupName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<class UTexture2D> GroupIcon;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<TObjectPtr<class UStructurePartAction>> Actions;
	
};
