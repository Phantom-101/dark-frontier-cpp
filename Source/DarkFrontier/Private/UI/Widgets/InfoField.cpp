// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/InfoField.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

void UInfoField::NativePreConstruct()
{
	Super::NativePreConstruct();

	IconImage->SetBrushFromTexture(Icon);
	LabelText->SetText(Label);
	ContentText->SetText(Content);
}

void UInfoField::SetContent(const FText& InContent) const
{
	ContentText->SetText(InContent);
}

void UInfoField::SetContentFromString(const FString& InContent) const
{
	ContentText->SetText(FText::FromString(InContent));
}

void UInfoField::SetContentFromFloat(const float InContent) const
{
	ContentText->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(InContent))));
}