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

	UpdateArc();
}

void UArc::SetThickness(float InThickness)
{
	ArcThickness = InThickness;
	
	UpdateArc();
}

void UArc::SetLength(const float Length)
{
	ArcLength = Length;

	UpdateArc();
}

void UArc::SetStartAndLength(const float Start, const float Length)
{
	ArcStart = Start;
	ArcLength = Length;

	UpdateArc();
}

void UArc::SetEndpoints(const float Start, const float End)
{
	ArcStart = Start;
	ArcLength = End - Start;

	UpdateArc();
}

void UArc::SetColor(const FLinearColor InColor)
{
	ArcColor = InColor;

	UpdateArc();
}

void UArc::UpdateArc() const
{
	if(MaterialInstance != nullptr)
	{
		MaterialInstance->SetScalarParameterValue("Thickness", ArcThickness);
		MaterialInstance->SetScalarParameterValue("Turn", ArcStart);
		MaterialInstance->SetScalarParameterValue("Percent", ArcLength);
		ArcImage->SetBrushTintColor(ArcColor);
	}
}
