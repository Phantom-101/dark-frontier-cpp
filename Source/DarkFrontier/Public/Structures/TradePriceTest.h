// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TradePriceTest.generated.h"

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UTradePriceTest : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UItem> Item;
	
	virtual void BeginPlay() override;

};
