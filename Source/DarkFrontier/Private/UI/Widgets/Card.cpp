// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Card.h"
#include "CommonBorder.h"

void UCard::NativePreConstruct()
{
	Super::NativePreConstruct();

	Header->SetVisibility(UseHeader ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
