// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Arc.h"
#include "Components/Image.h"

void UArc::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(ArcMaterial != nullptr)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(ArcMaterial, this);
		ArcImage->SetBrushFromMaterial(MaterialInstance);
	}

	if(MaterialInstance != nullptr)
	{
		MaterialInstance->SetScalarParameterValue("Turn", ArcStart);
		MaterialInstance->SetScalarParameterValue("Percent", ArcLength);
		ArcImage->SetBrushTintColor(ArcColor);
	}
}

void UArc::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(MaterialInstance != nullptr)
	{
		MaterialInstance->SetScalarParameterValue("Turn", ArcStart);
		MaterialInstance->SetScalarParameterValue("Percent", ArcLength);
		ArcImage->SetBrushTintColor(ArcColor);
	}
}

void UArc::SetLength(const float Start, const float Length)
{
	ArcStart = Start;
	ArcLength = Length;
}

void UArc::SetEndpoints(const float Start, const float End)
{
	ArcStart = Start;
	ArcLength = End - Start;
}

void UArc::SetColor(const FLinearColor InColor)
{
	ArcColor = InColor;
}
