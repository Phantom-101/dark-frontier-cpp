// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ListSelectionOptionParams.generated.h"

class UWidget;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UListSelectionOptionParams : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UListSelectionModal> OwningModal;

	UPROPERTY()
	TObjectPtr<UObject> Option;

	TFunction<UWidget* (UObject*)> Builder;
	
};
