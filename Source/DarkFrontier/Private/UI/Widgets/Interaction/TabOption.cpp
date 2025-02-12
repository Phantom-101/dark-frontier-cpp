// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/TabOption.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/Widgets/Interaction/Tab.h"

void UTabOption::Init(UTab* Tab) const
{
	IconImage->SetBrushFromTexture(Tab->GetIcon());
	NameText->SetText(Tab->GetName());
}
