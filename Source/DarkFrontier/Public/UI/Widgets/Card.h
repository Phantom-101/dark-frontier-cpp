// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Card.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCard : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonBorder> Header;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool UseHeader = true;

	virtual void NativePreConstruct() override;
	
public:


	
};
