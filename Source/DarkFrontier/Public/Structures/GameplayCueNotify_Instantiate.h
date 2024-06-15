// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_Instantiate.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UGameplayCueNotify_Instantiate : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

protected:

	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;
	
};
