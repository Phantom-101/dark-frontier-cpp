// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ListBoxOptionParams.generated.h"

class UListBox;
class UWidget;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UListBoxOptionParams : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UListBox> ListBox;

	UPROPERTY()
	TObjectPtr<UObject> Option;

	TFunction<UWidget* (UObject*)> Builder;
	
};
