// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InfoTab.generated.h"

class UInfoScreen;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoTab : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UInfoScreen> Screen;

public:

	virtual void Init(UInfoScreen* InScreen);
	
};
