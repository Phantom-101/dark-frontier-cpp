// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LogUniverseMapConnection.generated.h"

class ASector;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogUniverseMapConnection : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> From;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> To;

public:

	void Init(ASector* InFrom, ASector* InTo);
	
};
