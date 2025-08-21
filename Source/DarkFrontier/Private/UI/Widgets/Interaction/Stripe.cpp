// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/Stripe.h"
#include "CommonBorder.h"
#include "Libraries/UIFunctionLibrary.h"

void UStripe::SetStyle(const TSubclassOf<UCommonBorderStyle>& Style) const
{
	Border->SetStyle(Style);
}

void UStripe::SetIsVisible(const bool IsVisible)
{
	SetVisibility(IsVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}
