// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Stripe.generated.h"

class UListView;
class UCommonBorderStyle;
class UCommonBorder;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStripe : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBorder> Border;

public:

	void SetStyle(const TSubclassOf<UCommonBorderStyle>& Style) const;

	void SetIsVisible(bool IsVisible);

};
