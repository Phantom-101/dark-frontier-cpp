// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectIndicatorObject.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UGameplayEffectIndicatorObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FActiveGameplayEffectHandle EffectHandle;
	
};
