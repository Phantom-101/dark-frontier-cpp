// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectUIData.h"
#include "CustomGameplayEffectUIData.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCustomGameplayEffectUIData : public UGameplayEffectUIData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<class UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;
	
};
